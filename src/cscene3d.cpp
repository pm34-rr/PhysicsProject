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

#if defined(HAVE_QT5)
#include <QtWidgets>
#else
#include <QtGui>
#endif
#include "main.h"
#include "cscene3d.h"
#include <cmath>

unsigned long long int tot = 0;
int vfps = 10;
const static float pi=3.141593f, k=pi/180.0f;
int id_timer;
static float shift;
const int numOfSprings = 3;
Caction m_action[4];

GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 0.0f};     //фоновый свет
GLfloat light_diffuse[] = {0.5f, 0.5f, 0.5f, 0.0f};     //значение диффузного света
GLfloat light_position[] = {0.5f, 0.0f, 0.5f, 0.0f};    //позиция источника света

Cscene3D::Cscene3D(QWidget* parent) : QGLWidget(parent)
{
    xRot = -85.0f;
    yRot = 0.0f;
    zRot = 90.0f;
    zTra = 0.0f;
    nSca = 0.5f;
}

void Cscene3D::actiontime()
{
	for(int i=0;i<numOfSprings;i++)
    {
		tot += (long long unsigned int)(vfps * m_action[i].ktime);
		m_action[i].Refresh(tot);
    }
}


void Cscene3D::timerEvent(QTimerEvent *) // событие таймера
{
    updateGL(); // обновление изображения
}

void Cscene3D::initializeGL()
{
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    wall_left.loadModelData(":/data/m_wall_left.ms3d");
    wall_right.loadModelData(":/data/m_wall_right.ms3d");
    spring_start.loadModelData(":/data/m_spring_start.ms3d");
    spring_end.loadModelData(":/data/m_spring_end.ms3d");
    sphere.loadModelData(":/data/m_mass.ms3d");
    float balance = - 0.2 - 0.8 - (m_action[0].m * 9.81 / m_action[0].k);
    float spring_step = -0.3f;

    shift = ((((float)numOfSprings)-1.0)*fabs(balance+m_action[1].x)+(((float)numOfSprings)-1.0)*fabs(spring_step)+ fabs(balance+m_action[0].x))/2.0;

    for(int i = 0; i < numOfSprings; i++)
    {
        springs[i].loadModelData(":/data/m_cyllinder.ms3d");
        springs[i].init();
    }

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);    // Установка Фонового Света
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);    // Установка Диффузного Света
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);   // Позиция света

    glEnable(GL_LIGHTING);                              // Разрешить освещение
    glEnable (GL_LIGHT1);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_MULTISAMPLE);
}

void Cscene3D::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    

    GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;
    if (nWidth>=nHeight)
        glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 30.0);
    else
        glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 30.0);

    glViewport(0, 0,(GLint)nWidth, (GLint)nHeight);
}

/*основная функция рисования*/
void Cscene3D::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(nSca, nSca, nSca);
    glRotatef(xRot, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f,0.0f);

    float balance = - 0.2 - 0.8 - (0.01 * 9.81 / 50.0);
    float spring_step = -0.3f;
    glTranslatef(0.0f, shift, 0.0f);
    wall_left.draw();
    glTranslatef(0.0f, -2*shift, 0.0f);
    spring_end.draw();
    wall_right.draw();
    glTranslatef(0.0f, 2*shift, 0.0f);
    for(int i = 0; i < numOfSprings - 1; i++)
    {
    spring_start.draw();
    springs[i].resize(- m_action[i].x - balance);
    springs[i].draw();
    glTranslatef(0.0f, m_action[i].x + balance ,0.0f);
    sphere.draw();
    spring_end.draw();
    glTranslatef(0.0f, spring_step ,0.0f);
    }
    springs[numOfSprings - 1].resize(- m_action[numOfSprings - 1].x - balance);
    springs[numOfSprings - 1].draw();
    glTranslatef(0.0f, m_action[0].x + balance ,0.0f);



}

void Cscene3D::mousePressEvent(QMouseEvent* pe)
{
    ptrMousePosition = pe->pos();
}

void Cscene3D::mouseReleaseEvent(QMouseEvent*)
{
    updateGL();
}

void Cscene3D::mouseMoveEvent(QMouseEvent* pe)
{    
    xRot += 180/1.5*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
    zRot += 180/1.5*(GLfloat)(pe->x()-ptrMousePosition.x())/width();
    ptrMousePosition = pe->pos();
    updateGL();
}

void Cscene3D::wheelEvent(QWheelEvent* pe)
{
    if ((pe->delta())>0) scale_plus();
    else if ((pe->delta())<0) scale_minus();

    updateGL();
}

void Cscene3D::keyPressEvent(QKeyEvent* pe)
{
    switch (pe->key())
    {
    case Qt::Key_Plus:
        scale_plus();
        break;

    case Qt::Key_Equal:
        scale_plus();
        break;

    case Qt::Key_Minus:
        scale_minus();
        break;

    case Qt::Key_Up:
        rotate_up();
        break;

    case Qt::Key_Down:
        rotate_down();
        break;

    case Qt::Key_Left:
        rotate_left();
        break;

    case Qt::Key_Right:
        rotate_right();
        break;

    case Qt::Key_Z:
        translate_down();
        break;

    case Qt::Key_X:
        translate_up();
        break;

    case Qt::Key_Space:
        defaultScene();
        break;

    case Qt::Key_Escape:
        this->close();
        break;
    }

    updateGL();
}

void Cscene3D::scale_plus()
{
    if(nSca < 2.5f)
    {
        nSca = nSca * 1.1f;
        update_light();
    }
}

void Cscene3D::scale_minus()
{
    if(nSca > 0.1f)
    {
        nSca = nSca / 1.1f;
        update_light();
    }
}

void Cscene3D::rotate_up()
{
    xRot += 1.0f;
}

void Cscene3D::rotate_down()
{
    xRot -= 1.0f;
}

void Cscene3D::rotate_left()
{
    zRot += 1.0f;
}

void Cscene3D::rotate_right()
{
    zRot -= 1.0f;
}

void Cscene3D::translate_down()
{
    zTra -= 0.05f;
}

void Cscene3D::translate_up()
{
    zTra += 0.05f;
}

void Cscene3D::defaultScene()
{
    xRot = -90.0f;
    yRot = 0.0f;
    zRot = 0.0f;
    zTra = 0.0f;
    nSca = 1.0f;
}

// Обновление освещения при изменении масштаба
void Cscene3D::update_light()
{
    GLfloat light_diffuse_new[] =
    {
        light_diffuse[0] * 2.0f * nSca,
        light_diffuse[1] * 2.0f * nSca,
        light_diffuse[2] * 2.0f * nSca,
        light_diffuse[3]
    };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse_new);
}
