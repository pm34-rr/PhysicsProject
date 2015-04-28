#if defined(HAVE_QT5)
#include <QtWidgets>
#else
#include <QtGui>
#endif
#include "main.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "caction.h"

#if defined(_WIN32) || defined(WIN32)

#include <QFont>
#include <QFontDatabase>

#if defined(HAVE_OLD_QT)
#include <windows.h>
#endif

// Фикс шрифтов (замена стандартных на Tahoma, если стандартные не поддерживают кириллицу)
template<typename T> void fix_fonts(T * widget)
{
    static QFontDatabase qfd;
#if defined(HAVE_OLD_QT)
    static DWORD dwVersion = (DWORD)(LOBYTE(LOWORD(GetVersion())));
    if(!qfd.families(QFontDatabase::Cyrillic).contains(widget->font().family(), Qt::CaseInsensitive) || dwVersion <= 4)
#else
    if(!qfd.families(QFontDatabase::Cyrillic).contains(widget->font().family(), Qt::CaseInsensitive))
#endif
    {
        QFont font_tahoma = widget->font();
        font_tahoma.setFamily("Tahoma");
        widget->setFont(font_tahoma);
    }
}

#endif

bool go(false);


const int numOfSprings = 3;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#if defined(VERSION_NUMBER)
    setWindowTitle(trUtf8("Пружинный маятник в среде с сопротивлением") + QString(" ") + VERSION_NUMBER);
#else
    setWindowTitle(trUtf8("Пружинный маятник в среде с сопротивлением"));
#endif
    setCentralWidget(ui->widget);
    qtmr = new QTimer(this);
    connect(qtmr, SIGNAL(timeout()), ui->widget ,SLOT(actiontime()));
    connect(qtmr, SIGNAL(timeout()), ui->widget ,SLOT(updateGL()));
    connect(qtmr, SIGNAL(timeout()), this,SLOT(disptime()));
    ui->lcdNumber->setDecMode();
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);    
    //дефолтные значения(пример)
	for(int i=0;i<numOfSprings-1;i++)
    {
    m_action[i].m = 0.01;
	m_action[i].A0 = 0.3;
	m_action[i].x = 0.0;
    m_action[i].k = 50;
    m_action[i].r = 3;
    }


    ui->horizontalSlider->setValue(10);//масса груза m
	ui->horizontalSlider_2->setValue(80);//начальное смещение
    ui->horizontalSlider_3->setValue(50); //коэффициент жесткости k  
    ui->horizontalSlider_5->setValue(100);//скорость эксперимента
    buttonflag = io = false;
    vfps = 40;
    ui->horizontalSlider_6->setValue(vfps);

    // Фикс шрифтов
#if defined(_WIN32) || defined(WIN32)
    fix_fonts(this);
    fix_fonts(ui->menuBar);
    fix_fonts(ui->menu);
    fix_fonts(ui->menu_2);
    fix_fonts(ui->groupBox);
    fix_fonts(ui->groupBox_2);
    fix_fonts(ui->label);
    fix_fonts(ui->label_2);
    fix_fonts(ui->label_3);
    fix_fonts(ui->label_4);
    fix_fonts(ui->label_5);
    fix_fonts(ui->label_6);
    fix_fonts(ui->label_9);
    fix_fonts(ui->label_10);
    fix_fonts(ui->label_11);
    fix_fonts(ui->label_12);
    fix_fonts(ui->label_13);
    fix_fonts(ui->label_14);
    fix_fonts(ui->pushButton);
    fix_fonts(ui->pushButton_2);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //кнопка старт/пауза
    io = false;
    if(!buttonflag)
    {
        ui->horizontalSlider->setEnabled(false);
        ui->horizontalSlider_2->setEnabled(false);
        ui->horizontalSlider_3->setEnabled(false);       
        ui->pushButton->setText(trUtf8("Стоп"));
        buttonflag = true;
        qtmr->start(vfps);
        go = true;
    }
    else
    {       
        buttonflag = false;
        ui->pushButton->setText(trUtf8("Старт"));
        qtmr->stop();
        go = false;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    //кнопка стоп
    qtmr->stop();
    go = false;

    ui->horizontalSlider->setEnabled(true);
    ui->horizontalSlider_2->setEnabled(true);
    ui->horizontalSlider_3->setEnabled(true);
    ui->pushButton->setEnabled(true);
    tot = 0;
    io = false; 
    if(buttonflag)
        ui->pushButton->click();
	for(int i=0;i<numOfSprings-1;i++)
        m_action[i].x = m_action[i].A0;
    ui->lcdNumber->display(0);
    ui->widget->updateGL();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //масса груза m
    double v1;
    v1 = value/1000.0;
    v1 = ((int)(v1*100.0))/100.0;
	for(int i=0;i<numOfSprings-1;i++)
        m_action[i].m = v1;
    QString st;
    st = QString::number(v1);
    ui->label_2->setText(st);
	for(int i=0;i<numOfSprings-1;i++)
        m_action[i].InitBall();
    ui->widget->updateGL();   
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    //начальное смещение
    double v1;
    v1 = value/100.0 - 0.8;
    if(fabs(v1) < 0.001)
        v1 =0.0;
    m_action[0].A0 = m_action[0].x = v1;
    m_action[0].InitBall();
    QString st;
    st = QString::number(v1);
    ui->label_4->setText(st);
    ui->widget->updateGL();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    //коэффициент жесткости k
	for(int i=0;i<numOfSprings-1;i++)
    {
        m_action[i].k = value;
        m_action[i].InitBall();
    }
    QString st;
    st = QString::number(value);
    ui->label_6->setText(st);
    ui->widget->updateGL();
}



void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    //скорость эксперимента
    QString st;
    st = QString::number(value);
    ui->label_10->setText(st);
	for(int i=0;i<numOfSprings-1;i++)
    {
        m_action[i].ktime = value/100.0;
        m_action[i].InitBall();
    }
    ui->widget->updateGL();   
}


void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
    //качество картинки
    vfps = value;
    qtmr-> stop();
    if(go)
        qtmr->start(vfps);
}

void MainWindow::disptime()
{
    QString str;
    //str.setNum(tot/1000.0,g,2); //WTF?
    str.setNum(tot/1000.0,10,2);
    ui->lcdNumber->display(str);

}

