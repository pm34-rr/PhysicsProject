#pragma once

#include <QtWidgets/QMenuBar>

class AppMenu : public QMenuBar
{
	Q_OBJECT

public:
	AppMenu( QWidget * parent = 0 );
	~AppMenu();

	void showGraphXt();
	void showGraphVt();
	void showGraphVx();

	void showAboutExperiment();
	void showAboutDevelopers();
};
