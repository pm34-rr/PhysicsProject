#include "WindowDevelopers.h"

#include <QtWidgets/QLabel>

WindowDevelopers::WindowDevelopers( QWidget * parent ):
	QWidget( nullptr )
{
	resize( 600, 300 );

	setAttribute( Qt::WA_DeleteOnClose );
	QPalette pal;
	pal.setBrush( this->backgroundRole(), Qt::white );
	setPalette( pal );
	setAutoFillBackground( true );

	setWindowTitle( tr( "Virtual labratoty: free oscillations of connected spring pendulums" ) );


	QLabel * students = new QLabel( tr( "Students" ), this );
	students->setStyleSheet( "font: 20px bold;" );
	students->setAlignment( Qt::AlignCenter );
	students->resize( width(), students->height() );
	students->move( 0, 15 );

	const int LEFT_PADDING = 0;
	const int STUDENTS_BETWEEN_PADDING = -5;
	const int HEADER_PADDING = 30;
	QLabel * first = new QLabel( tr ( "Bunyakov Igor Dmitrievich, PM-34" ), this );
	first->setAlignment( Qt::AlignCenter );
	first->resize( width(), first->height() );
	first->move( LEFT_PADDING, students->y() + HEADER_PADDING );
	QLabel * second = new QLabel( tr ( "Rogoza Alexandr Andreevich, PM-34" ), this );
	second->setAlignment( Qt::AlignCenter );
	second->resize( width(), second->height() );
	second->move( first->x(), first->y() + first->height() + STUDENTS_BETWEEN_PADDING );
	QLabel * third = new QLabel( tr( "Romanov Stanislav Alexandrovich, PM-34" ), this );
	third->setAlignment( Qt::AlignCenter );
	third->resize( width(), third->height() );
	third->move( third->x(), second->y() + second->height() + STUDENTS_BETWEEN_PADDING );

	QLabel * lector = new QLabel( tr( "Lector" ), this );
	lector->setStyleSheet( "font: 20px bold;" );
	lector->setAlignment( Qt::AlignCenter );
	lector->resize( width(), lector->height() );
	lector->move( 0, third->y() + third->height() + 15 );

    QLabel * lfirst = new QLabel( tr( "Baranov Alexandr Viktorovich, Candidate of Physical and Mathematical Sciences, Associate Professor of \"General Physics\" NSTU" ), this );
	lfirst->setAlignment( Qt::AlignCenter );
	lfirst->resize( width(), lfirst->height() );
	lfirst->move( LEFT_PADDING, lector->y() + HEADER_PADDING );
}

WindowDevelopers::~WindowDevelopers()
{

}

