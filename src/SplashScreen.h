#pragma once

#include <QtWidgets/QLabel>
#include <QtCore/QTimer>

class SplashScreen : public QLabel
{
	Q_OBJECT

public:
	SplashScreen( QWidget * parent = 0 );
	~SplashScreen();

	void startTimer();
	void createMainWindow();

protected:
	void keyPressEvent( QKeyEvent *ev );

private:
	QTimer m_timer;
};

