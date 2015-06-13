#include <QApplication>
#include "mainwindow.h"

int main( int argc, char * argv[] )
{
    QGLFormat fmt;
    fmt.setSampleBuffers(true);
    fmt.setSamples(16); // 2, 4, 8, 16
    QGLFormat::setDefaultFormat(fmt);

	QApplication app( argc, argv );

	MainWindow w;
	w.show();

	return app.exec();
}
