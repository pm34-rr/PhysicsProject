#include "manual.h"
#include "ui_manual.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPoint>

Manual::Manual(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manual)
{
    ui->setupUi(this);

	setAttribute( Qt::WA_DeleteOnClose );

    QPoint center = QApplication::desktop()->availableGeometry().center();
    QPoint corner = QApplication::desktop()->availableGeometry().topLeft();
    center.setX(center.x() - this->width() / 2);
    center.setY(center.y() - this->height() / 2);
    if(center.x() <= corner.x() || center.y() <= corner.y())
        this->move(corner);
    else
        this->move(center);
}

Manual::~Manual()
{
    delete ui;
}
