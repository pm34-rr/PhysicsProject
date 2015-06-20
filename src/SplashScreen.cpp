#include "SplashScreen.h"

#include <QtGui/QBitmap>
#include <QtGui/QKeyEvent>

#include "mainwindow.h"

SplashScreen::SplashScreen( QWidget * parent ) :
QLabel( parent )
{
	setWindowFlags( Qt::FramelessWindowHint | Qt::Window );
	QPixmap pixmap( ":/Splash.png" );
	setPixmap( pixmap );
	setMask( pixmap.mask() );
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::keyPressEvent( QKeyEvent *ev )
{
	if ( ev->key() == Qt::Key_Escape ) {
		close();
		m_timer.stop();
		createMainWindow();
	}
}

void SplashScreen::startTimer()
{
	m_timer.setSingleShot( true );

	connect( &m_timer, &QTimer::timeout, this, &SplashScreen::close );
	connect( &m_timer, &QTimer::timeout, this, &SplashScreen::createMainWindow );
	
	m_timer.start( 10 * 1000 );
}

void SplashScreen::createMainWindow()
{
	MainWindow * window = new MainWindow;
	window->show();
}
