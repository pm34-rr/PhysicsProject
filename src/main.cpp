#include <QtWidgets/QApplication>

#include "mainwindow.h"
#include "SplashScreen.h"

int main( int argc, char * argv[] )
{
    QGLFormat fmt;
	fmt.setSampleBuffers( true );
	fmt.setSamples( 16 );
    QGLFormat::setDefaultFormat(fmt);

	QApplication app( argc, argv );

	QTranslator myTranslator;
	myTranslator.load( ":/PhysicsProject_ru.qm" );
	app.installTranslator( &myTranslator );

	SplashScreen screen;
	screen.show();
	screen.startTimer();

	return app.exec();
}
