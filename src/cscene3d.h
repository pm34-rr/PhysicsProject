#ifndef CSCENE3D_H
#define CSCENE3D_H

/* класс 3D сцены в главном окне*/
#include <QGLWidget>
#include "cmodel.h"
#include <QtOpenGL>

#if !defined(GL_MULTISAMPLE)
#define GL_MULTISAMPLE  0x809D
#endif

class Calculations;

class Cscene3D : public QGLWidget
{
    Q_OBJECT

public:
	Cscene3D(QWidget* parent = 0);
	void prepareBodies();
	void actiontime();
	void clear();


protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent* pe);
    void keyPressEvent(QKeyEvent* pe);
    void timerEvent(QTimerEvent *); // обработка события таймера

private:
	//модели
	CMilkshapeModel wall_left, wall_right, spring_start, spring_end, sphere;
	CModelSpring springs[5];

	GLfloat xRot;
	GLfloat yRot;
	GLfloat zRot;
	GLfloat zTra;
	GLfloat nSca;

	QPoint ptrMousePosition;

	Calculations * _calculations;
	std::vector<double> _tempArray;

	//реакция на клавиши и мышь
	void scale_plus();
	void scale_minus();
	void rotate_up();
	void rotate_down();
	void rotate_left();
	void rotate_right();
	void translate_down();
	void translate_up();
	void defaultScene();
	// Обновление освещения при изменении масштаба
	void update_light();
};

#endif // CSCENE3D_H
