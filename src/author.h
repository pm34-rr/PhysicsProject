/* 
   Copyright (C) 2011-2013,
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

   // some changes

#ifndef AUTHOR_H
#define AUTHOR_H

#include <QMainWindow>

namespace Ui {
class author;
}

class author : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit author(QWidget *parent = 0);
    ~author();
    
private:
    Ui::author *ui;
};

#endif // AUTHOR_H
