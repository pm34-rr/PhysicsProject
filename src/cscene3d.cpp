#include "cscene3d.h"

#include "main.h"
#include "Storage.h"
#include "Calculations.h"

#include <cmath>

#include <QtWidgets>


unsigned long long int tot = 0;
int vfps = 10;
const static float pi=3.141593f, k=pi/180.0f;
int id_timer;
static float shift;                                     //половина длины всей установки
const float GRAY_TINT = 0.8f;

Caction m_action[4];

GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 0.0f};     //фоновый свет
GLfloat light_diffuse[] = {0.5f, 0.5f, 0.5f, 0.0f};     //значение диффузного света
GLfloat light_position[] = {0.5f, 0.0f, 0.5f, 0.0f};    //позиция источника света

Cscene3D::Cscene3D( QWidget * parent ):
	QGLWidget( parent )
{
    xRot = -85.0f;
    yRot = 0.0f;
    zRot = 90.0f;
    zTra = 0.0f;
	nSca = 0.5f;
}

void Cscene3D::prepareBodies()
{
	int n = theStorage.getNumOfSprings() - 1;
	_tempArray.resize( n, 0 );
	for ( int i = 0; i < n; ++i )
		_tempArray[i] = 0;
	for ( int i = 0; i < n; ++i )
		_tempArray[i] = m_action[i].x0;

	theCalcs.initializeCalculations( n, m_action[0].k, m_action[0].m, _tempArray );
}

void Cscene3D::actiontime()
{
	tot += (long long unsigned int)( vfps * m_action[0].ktime );
	double t = tot / 1000.0;
	theCalcs.calculateShifts( t, _tempArray );
	int n = _tempArray.size();
	for ( int i = 0; i < n; ++i )
		m_action[i].x = _tempArray[i];

	updateGL();
}

void Cscene3D::clear()
{
	tot = 0;
	theCalcs.clear();
}

void Cscene3D::timerEvent(QTimerEvent *)
{
	updateGL();
}

void Cscene3D::initializeGL()
{
	glClearColor( GRAY_TINT, GRAY_TINT, GRAY_TINT, 0.0 );
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    wall_left_2.loadModelData(":/data/m_wall_left_2.ms3d");
    wall_left_3.loadModelData(":/data/m_wall_left_3.ms3d");
    wall_left_4.loadModelData(":/data/m_wall_left_4.ms3d");
    wall_right.loadModelData(":/data/m_wall_right.ms3d");
    spring_start.loadModelData(":/data/m_spring_start.ms3d");
    spring_end.loadModelData(":/data/m_spring_end.ms3d");
    sphere.loadModelData(":/data/m_mass.ms3d");
    float balance = - 0.2 - 0.8 - (m_action[0].m * 9.81 / m_action[0].k);
    float spring_step = -0.3f;

	int n = 5;
	shift = ((((float)n)-1.0)*fabs(balance+m_action[1].x)+(((float)n)-1.0)*fabs(spring_step)+ fabs(balance+m_action[0].x))/2.0;

	for(int i = 0; i < n; i++) {
        springs[i].loadModelData(":/data/m_cyllinder.ms3d");
        springs[i].init();
    }

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);    // Установка Фонового Света
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);    // Установка Диффузного Света
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);  // Позиция света

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

void Cscene3D::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glScalef(nSca, nSca, nSca);
	glRotatef(xRot, 0.0f, -1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f,0.0f);

    int n = theStorage.getNumOfSprings() - 1;

	float balance = - 0.2 - 0.8 - (0.01 * 9.81 / 50.0);
	float spring_step = -0.3f;
	glTranslatef(0.0f, shift, 0.0f);
    switch(n)
	{
		case 2:
			wall_left_2.draw(); break;
		case 3:
			wall_left_3.draw(); break;
		case 4:
			wall_left_4.draw(); break;
	}

	glTranslatef(0.0f, -2*shift, 0.0f);
	spring_end.draw();
	wall_right.draw();
	glTranslatef(0.0f, 2*shift, 0.0f);
	double springs_length = 0;


	shift =( -(n+1)*balance - n*spring_step)/2.0;

	for(int i = 0; i < n; i++) {
		if( i != 0) {
			springs[i].resize( m_action[i-1].x - balance - m_action[i].x);
			glTranslatef(0.0f, i*(balance+spring_step) + m_action[i-1].x ,0.0f);
            spring_start.draw();
			springs[i].draw();
			glTranslatef(0.0f, -i*(balance+spring_step) - m_action[i-1].x ,0.0f);
		}
		else {
            spring_start.draw();
			springs[i].resize(- m_action[i].x - balance);
			springs[i].draw();            
		}

		glTranslatef(0.0f, m_action[i].x + (i+1)*balance + i*spring_step,0.0f);
		sphere.draw();
		spring_end.draw();
		glTranslatef(0.0f, spring_step ,0.0f);
		springs_length += spring_step - m_action[i].x + balance;
		glTranslatef(0.0f, -(i+1)*(balance + spring_step) - m_action[i].x ,0.0f);
	}
	glTranslatef(0.0f, n*(balance+spring_step) + m_action[n-1].x ,0.0f);
	spring_start.draw();
	springs[n].resize(2*shift + n*balance + n*spring_step + m_action[n-1].x);
	springs[n].draw();
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
	if ( nSca < 2.5f ) {
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

void Cscene3D::rotate_right()
{
    xRot += 1.0f;
}

void Cscene3D::rotate_left()
{
    xRot -= 1.0f;
}

void Cscene3D::rotate_down()
{
    zRot += 1.0f;
}

void Cscene3D::rotate_up()
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
