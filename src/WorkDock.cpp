#include "WorkDock.h"

#include <QtWidgets/QSlider>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>

WorkDock::WorkDock( QWidget * parent ):
	QWidget( parent )
{
	setFixedWidth( 200 );

	QLabel * startingData = new QLabel( tr( "Starting data" ) );
	QLabel * massLabel = new QLabel( tr( "Bodys\' mass [kg]" ) );
	_massSlider = new QSlider( Qt::Horizontal );
	_massSlider->setFocusPolicy( Qt::NoFocus );
	_massLabelNum = new QLabel( "0.25" );

	QLabel * kLabel = new QLabel( tr( "Stiffness coefficient [N/m]" ) );
	_kSlider = new QSlider( Qt::Horizontal );
	_kSlider->setFocusPolicy( Qt::NoFocus );
	_kLabelNum = new QLabel( "50" );

	QLabel * xLabel = new QLabel( tr( "Starting shift of the 1st bodym]" ) );
	_xSlider = new QSlider( Qt::Horizontal );
	_xSlider->setFocusPolicy( Qt::NoFocus );
	_xLabelNum = new QLabel( "0" );

	QLabel * timeLabel = new QLabel( tr( "Time [s]" ) );
	_timerNumber = new QLCDNumber;


	QLabel * controlPanel = new QLabel( tr( "Control panel" ) );
	QLabel * speedLabel = new QLabel( tr( "Experiment speed [%]" ) );
	_speedSlider = new QSlider( Qt::Horizontal );
	_speedSlider->setFocusPolicy( Qt::NoFocus );
	_speedLabelNum = new QLabel( "100" );

	QLabel * graphicsLabel = new QLabel( tr( "Graphics" ) );
	_graphicsSlider = new QSlider( Qt::Horizontal );
	_graphicsSlider->setFocusPolicy( Qt::NoFocus );
	QLabel * graphicsSpeed = new QLabel( tr( "Speed" ) );
	QLabel * graphicsQuality = new QLabel( tr( "Quality" ) );

	_startButton = new QPushButton( tr( "Start" ) );
	_resetButton = new QPushButton( tr( "Reset" ) );



	// ========================================================================================
	// ======================== Layouts' part =================================================
	// ========================================================================================

	const int SPACING = 5;

	QVBoxLayout * fixedLayout1 = new QVBoxLayout;
	fixedLayout1->addWidget( massLabel );

	QHBoxLayout * massHLayout = new QHBoxLayout;
	massHLayout->addWidget( _massSlider );
	massHLayout->addWidget( _massLabelNum );

	fixedLayout1->addLayout( massHLayout );
	fixedLayout1->addWidget( kLabel );

	QHBoxLayout * kHLayout = new QHBoxLayout;
	kHLayout->addWidget( _kSlider );
	kHLayout->addWidget( _kLabelNum );

	fixedLayout1->addLayout( kHLayout );

	fixedLayout1->addWidget( xLabel );

	QHBoxLayout * xHLayout = new QHBoxLayout;
	xHLayout->addWidget( _xSlider );
	xHLayout->addWidget( _xLabelNum );

	fixedLayout1->addLayout( xHLayout );

	QVBoxLayout * startingDataLayout = new QVBoxLayout;
	startingDataLayout->addWidget( startingData );

	QHBoxLayout * fixedLayout11 = new QHBoxLayout;
	fixedLayout11->addSpacing( SPACING );
	fixedLayout11->addLayout( fixedLayout1 );
	startingDataLayout->addLayout(fixedLayout11 );

	QVBoxLayout * timeLayout = new QVBoxLayout;
	timeLayout->addWidget( timeLabel );
	timeLayout->addWidget( _timerNumber );

	QVBoxLayout * fixedLayout2 = new QVBoxLayout;
	fixedLayout2->addWidget( speedLabel );

	QHBoxLayout * speedLyt = new QHBoxLayout;
	speedLyt->addWidget( _speedSlider );
	speedLyt->addWidget( _speedLabelNum );

	fixedLayout2->addLayout( speedLyt );
	fixedLayout2->addWidget( graphicsLabel );
	fixedLayout2->addWidget( _graphicsSlider );

	QHBoxLayout * speedQua = new QHBoxLayout;
	speedQua->addWidget( graphicsSpeed );
	speedQua->addStretch( 5 );
	speedQua->addWidget( graphicsQuality );

	fixedLayout2->addLayout( speedQua );

	QHBoxLayout * fixedLayout21 = new QHBoxLayout;
	fixedLayout21->addSpacing( SPACING );
	fixedLayout21->addLayout( fixedLayout2 );

	QVBoxLayout * controlPanelLyt = new QVBoxLayout;
	controlPanelLyt->addWidget( controlPanel );
	controlPanelLyt->addLayout( fixedLayout21 );

	QVBoxLayout * mainLyt = new QVBoxLayout;
	mainLyt->addLayout( startingDataLayout );
	mainLyt->addSpacing( 80 );
	mainLyt->addLayout( timeLayout );
	mainLyt->addSpacing( 80 );
	mainLyt->addLayout( controlPanelLyt );

	setLayout( mainLyt );
}

WorkDock::~WorkDock()
{

}

