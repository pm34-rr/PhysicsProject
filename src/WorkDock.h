#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QVector>

class QSlider;
class QPushButton;
class QLCDNumber;
class QLabel;
class QComboBox;

class WorkDock : public QWidget
{
	Q_OBJECT

public:
	WorkDock( QWidget * parent = 0 );
	~WorkDock();

	void setTime( QString );

private:
	void changeLayoutsAndBodies( int bodiesCount );
	void disableItems( bool dicision );

	void experimentStarts();
	void experimentResets();
	void changeMass( int weight );
	void changeK( int k );
	void changeShift1( int x );
	void changeShift2( int x );
	void changeShift3( int x );
	void changeShift4( int x );
	void changeSpeed( int speed );
	void changeQuality( int q, bool started );

	void needUpdateGL();

	bool			_started;

	QLabel *		_bodiesCount;
	QComboBox *		_bodyCountBox;

	QLabel *		_startingDataLabel;
	QLabel *		_massLabel;
	QSlider	*		_massSlider;
	QLabel *		_massLabelNum;

	QVector<QLabel*>	_xLabel;
	QVector<QSlider*>	_xSlider;
	QVector<QLabel*>	_xLabelNum;

	QLabel *		_kLabel;
	QSlider *		_kSlider;

	QSlider *		_speedSlider;
	QSlider *		_graphicsSlider;

	QLabel *		_timeLabel;
	QLCDNumber *	_timerNumber;

	QPushButton *	_startButton;
	QPushButton *	_resetButton;

	QLabel *		_kLabelNum;

	QLabel *		_controlPanelLabel;
	QLabel *		_speedLabel;
	QLabel *		_speedLabelNum;
	QLabel *		_graphicsLabel;
	QLabel *		_qualityLabelNum;
	QLabel *		_graphicsSpeed;
	QLabel *		_graphicsQuality;

signals:
	void experimentStarted();
	void experimentStopped();
	void experimentReset();

	void stringsCountChanged( int );
	void massChanged( float );
	void kChanged( float );
	void shiftChanged( int, float );
	void speedChanged( int );
	void qualityChanged( int, bool );
};
