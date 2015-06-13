#include "AppMenu.h"

#include "Plot.h"

AppMenu::AppMenu( QWidget * parent ):
	QMenuBar( parent )
{
	QMenu * graphicsMenu = new QMenu( tr( "&Graphics" ), this );
	QMenu * aboutMenu = new QMenu( tr( "&About" ), this );

	QAction * graphics_xt = new QAction( tr( "Dependence X from t" ), graphicsMenu );
	QAction * graphics_vt = new QAction( tr( "Dependence V from t" ), graphicsMenu );
	QAction * graphics_vx = new QAction( tr( "Dependence X from V" ), graphicsMenu );
	graphicsMenu->addAction( graphics_xt );
	graphicsMenu->addAction( graphics_vt );
	graphicsMenu->addAction( graphics_vx );
	connect( graphics_xt, &QAction::triggered, this, &AppMenu::showGraphXt );
	connect( graphics_vt, &QAction::triggered, this, &AppMenu::showGraphVt );
	connect( graphics_vx, &QAction::triggered, this, &AppMenu::showGraphVx );

	addMenu( graphicsMenu );

	QAction * about_experiment = new QAction( tr( "About axperiment" ), aboutMenu );
	QAction * about_developers = new QAction( tr( "About developers" ), aboutMenu );
	aboutMenu->addAction( about_experiment );
	aboutMenu->addAction( about_developers );
	connect( about_experiment, &QAction::triggered, this, &AppMenu::showAboutExperiment );
	connect( about_developers, &QAction::triggered, this, &AppMenu::showAboutDevelopers );

	addMenu( aboutMenu );
}

AppMenu::~AppMenu()
{

}

void AppMenu::showGraphXt()
{
	Graph * graph = new Graph( "xt" );
	graph->show();
}

void AppMenu::showGraphVt()
{
	Graph * graph = new Graph( "vt" );
	graph->show();
}

void AppMenu::showGraphVx()
{
	Graph * graph = new Graph( "vx" );
	graph->show();
}

void AppMenu::showAboutExperiment()
{

}

void AppMenu::showAboutDevelopers()
{

}

