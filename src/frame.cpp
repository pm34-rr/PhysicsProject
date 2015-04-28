/* 
   Copyright (C) 2011-2014,
        Mikhail Alexandrov  <alexandroff.m@gmail.com>
        Andrey Kurochkin    <andy-717@yandex.ru>
        Peter Zhigalov      <peter.zhigalov@gmail.com>

   This file is part of the `pendulum' program.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "frame.h"
#include "ui_frame.h"

// Для запуска по центру экрана
#include <QApplication>
#include <QDesktopWidget>
#include <QPoint>

Frame::Frame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Frame)
{
    ui->setupUi(this);
    keydown = false;
    connect(ui->label, SIGNAL(destroyed()), SLOT(close()));

    // Перемещение в центр экрана
    QPoint center = QApplication::desktop()->availableGeometry().center();
    QPoint corner = QApplication::desktop()->availableGeometry().topLeft();
    center.setX(center.x() - this->width() / 2);
    center.setY(center.y() - this->height() / 2);
    if(center.x() <= corner.x() || center.y() <= corner.y())
        this->move(corner);
    else
        this->move(center);
}
/*удаление окна по времени или по нажатию клавиши*/
void Frame::timerEvent(QTimerEvent *event) // событие таймера
{
    static int dl(0);
    dl += 10;
    if( keydown || dl == 10000 || !this->isVisible() )
    {
        delete ui->label;
        killTimer(event->timerId());
    }
    else if(!this->isActiveWindow() && dl <= 1000)
    {
        this->activateWindow();
    }
}

void Frame::keyPressEvent(QKeyEvent* )
{
    keydown = true;
}

Frame::~Frame()
{
    delete ui;
}
