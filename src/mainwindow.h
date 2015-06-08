#pragma once

#include <QMainWindow>
#include <QFrame>
#include "cscene3d.h"

class WorkDock;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
	explicit MainWindow( QWidget * parent = 0 );
	~MainWindow();

	void startExperiment();
	void stopExperiment();
	void resetExperiment();

	void changeBodiesCout( int n );
	void changeMass( float mass );
	void changeK( int k );
	void changeShift( int i, float x );
	void changeSpeed( int s );
	void changeQuality( int q, bool started );

	QTimer * qtmr;
	bool buttonflag, io;

private slots:
	void displayTime();

private:
	QWidget *			_mainWidget;
	WorkDock *			_workDock;
	Ui::MainWindow *	ui;
};
