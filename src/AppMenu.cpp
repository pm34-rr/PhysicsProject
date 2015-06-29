#include "AppMenu.h"

#include "Plot.h"
#include "WindowDevelopers.h"
#include "manual.h"

AppMenu::AppMenu( QWidget * parent ):
	QMenuBar( parent )
{
	QMenu * graphicsMenu = new QMenu( tr( "&Graphics" ), this );
	QMenu * aboutMenu = new QMenu( tr( "&About" ), this );

	QAction * graphics_xt = new QAction( tr( "Dependence X from t" ), graphicsMenu );
	QAction * graphics_vt = new QAction( tr( "Dependence V from t" ), graphicsMenu );
	graphicsMenu->addAction( graphics_xt );
	graphicsMenu->addAction( graphics_vt );
	connect( graphics_xt, &QAction::triggered, this, &AppMenu::showGraphXt );
	connect( graphics_vt, &QAction::triggered, this, &AppMenu::showGraphVt );

	addMenu( graphicsMenu );

	QAction * about_experiment = new QAction( tr( "Manual" ), aboutMenu );
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
	QWidget * prnt = dynamic_cast<QWidget*>( parent() );
	Graph * graph = new Graph( prnt, "xt" );
	graph->show();
}

void AppMenu::showGraphVt()
{
	QWidget * prnt = dynamic_cast<QWidget*>( parent() );
	Graph * graph = new Graph( prnt, "vt" );
	graph->show();
}

void AppMenu::showAboutExperiment()
{
	Manual * manual = new Manual;
	manual->show();
}

void AppMenu::showAboutDevelopers()
{
	WindowDevelopers * about = new WindowDevelopers( this );
	about->show();
}

