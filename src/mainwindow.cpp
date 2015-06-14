#include "mainwindow.h"

#include "AppMenu.h"
#include "WorkDock.h"
#include "Storage.h"
#include "main.h"
#include "ui_mainwindow.h"
#include "caction.h"

#include <QtWidgets>
#include <QFont>
#include <QFontDatabase>
#include <QtWidgets/QBoxLayout>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui( new Ui::MainWindow )
{
	AppMenu * menu = new AppMenu( this );
	setMenuBar( menu );

	int n = 4;
	for ( int i = 0; i < n; i++) {
		m_action[i].m = 0.2;
		m_action[i].A0 = 0;
		m_action[i].x = 0.0;
		m_action[i].x0 = 0.0;
		m_action[i].k = 25;
		m_action[i].ktime = 1;
	}

	ui->setupUi( this );
	_workDock = new WorkDock;
	_mainWidget = new QWidget;

	QHBoxLayout * mainLyt = new QHBoxLayout;
	mainLyt->addWidget( ui->widget );
	mainLyt->addWidget( _workDock );
	_mainWidget->setLayout( mainLyt );

	setMinimumHeight( 768 );

	setCentralWidget( _mainWidget );
	qtmr = new QTimer( this );
	connect( qtmr, &QTimer::timeout, ui->widget, &Cscene3D::actiontime );
	connect( qtmr, &QTimer::timeout, this, &MainWindow::displayTime );

	connect( _workDock, &WorkDock::experimentStarted, this, &MainWindow::startExperiment );
	connect( _workDock, &WorkDock::experimentReset, this, &MainWindow::resetExperiment );
	connect( _workDock, &WorkDock::experimentStopped, this, &MainWindow::stopExperiment );

	connect( _workDock, &WorkDock::massChanged, this, &MainWindow::changeMass );
	connect( _workDock, &WorkDock::kChanged, this, &MainWindow::changeK );
	connect( _workDock, &WorkDock::shiftChanged, this, &MainWindow::changeShift );
	connect( _workDock, &WorkDock::speedChanged, this, &MainWindow::changeSpeed );
	connect( _workDock, &WorkDock::qualityChanged, this, &MainWindow::changeQuality );
	connect( _workDock, &WorkDock::stringsCountChanged, this, &MainWindow::changeBodiesCout );

	connect( _workDock, &WorkDock::needResize, this, &MainWindow::increaseHeight );
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::startExperiment()
{
	ui->widget->prepareBodies();
	qtmr->start( vfps );
}

void MainWindow::stopExperiment()
{
	qtmr->stop();
}

void MainWindow::resetExperiment()
{
	qtmr->stop();
	int n = theStorage.getNumOfSprings() - 1;
	for ( int i = 0; i < n; i++ ) {
		m_action[i].x = 0;
	}
	ui->widget->clear();
	ui->widget->updateGL();
}

void MainWindow::changeBodiesCout( int n )
{
	n--;
	ui->widget->updateGL();

}

void MainWindow::changeMass( float mass )
{
	int n = theStorage.getNumOfSprings() - 1;
	for( int i = 0; i < n; i++ )
		m_action[i].m = mass;
	ui->widget->updateGL();
}

void MainWindow::changeK( int k )
{
	int n = theStorage.getNumOfSprings() - 1;
	for ( int i = 0; i < n; i++ )
		m_action[i].k = k;
	ui->widget->updateGL();
}

void MainWindow::changeShift( int i, float x )
{
	int n = theStorage.getNumOfSprings() - 1;
	int a = n-i-1;
	m_action[a].x0 = m_action[a].x = x;
	ui->widget->updateGL();
}

void MainWindow::changeSpeed( int s )
{
	int n = theStorage.getNumOfSprings() - 1;
	for ( int i = 0; i < n; i++ )
		m_action[i].ktime = s / 100.0;
	ui->widget->updateGL();
}

void MainWindow::changeQuality( int q , bool started )
{
	vfps = q;
	qtmr-> stop();
	if( started )
		qtmr->start( q );
}

void MainWindow::displayTime()
{
    QString str;
	str.setNum( tot / 1000.0, 10, 2);
	_workDock->setTime( str );
}

void MainWindow::increaseHeight( int n )
{
	resize( width(), height() + n*42 );
}
