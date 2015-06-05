#pragma once

#include <QtWidgets/QWidget>

class QSlider;
class QPushButton;
class QLCDNumber;
class QLabel;

class WorkDock : public QWidget
{
	Q_OBJECT

public:
	WorkDock( QWidget * parent = 0 );
	~WorkDock();

private:
	QSlider	*		_massSlider;
	QSlider *		_xSlider;
	QSlider *		_kSlider;

	QSlider *		_speedSlider;
	QSlider *		_graphicsSlider;

	QLCDNumber *	_timerNumber;

	QPushButton *	_startButton;
	QPushButton *	_resetButton;

	QLabel *		_massLabelNum;
	QLabel *		_xLabelNum;
	QLabel *		_kLabelNum;

	QLabel *		_speedLabelNum;
	QLabel *		_qualityLabelNum;
};
