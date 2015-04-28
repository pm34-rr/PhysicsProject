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

#include "caction.h"

Caction::Caction()
{
    x = A0;
}

Caction::~Caction()
{

}

void Caction::InitBall()
{
    fita = 0;
    x = A0;
    w0 = sqrt(k / m);
    sigma = r / (2 * m);
  //  if(w0>r/2/m)
   // {
		w = w0;
		T = 2 * pi1*w0;
		AtimeT = A0 * cos(w * T + fita);
        ldekrem = log(A0 / AtimeT);
   // }
   // else
   //     w = 0;
    Q = w0 / 2 / sigma;
    oldx = A0;
    oldtime = -1;
    v = 0;
    E0 = k * A0 * A0 / 2;
    E=E0;
}

void Caction::Refresh(double Ntime)
{
    double t = Ntime / 1000.0;
		x = A0 * cos(w * t + fita);
        v = (x - oldx) / (t - oldtime);
        oldx = x;
        oldtime = t;       
}
