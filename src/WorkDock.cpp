#include "WorkDock.h"

#include "Storage.h"

#include <QtGui/QPixmap>
#include <QtGui/QBitmap>
#include <QtGui/QPainter>

#include <QtWidgets/QSlider>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QBoxLayout>



const int PADDING = 0;
const int PART_PADDING = 15;
const int LEFT_LEFT_ALIGN = 9;
const int LEFT_ALIGN = LEFT_LEFT_ALIGN + 6;

WorkDock::WorkDock( QWidget * parent ):
	QWidget( parent )
{
	const int WIDGET_WIDTH = 255;
	const int FIRST_ITEM_Y = 10;
	const QSize SLIDER_SIZE( WIDGET_WIDTH - 50, 20 );
	const QSize TIMER_SIZE( 50, 50 );
	const QSize BUTTON_SIZE( (WIDGET_WIDTH - 3 * LEFT_LEFT_ALIGN) / 2, 40 );
	const int LABEL_NUM_WIDTH = 40;

	const int AFTER_SLDIER_PADDDING = 5;

	const int LEFT_SHIFT_BORDER = -40;
	const int RIGHT_SHIFT_BORDER = - LEFT_SHIFT_BORDER;

	setFixedWidth( WIDGET_WIDTH );
	setMinimumHeight( 768 );

	_started = false;

	_bodiesCount = new QLabel( tr( "Bodies count" ), this );
	_bodiesCount->move( LEFT_LEFT_ALIGN, FIRST_ITEM_Y );
	_bodyCountBox = new QComboBox( this );
	_bodyCountBox->move( LEFT_LEFT_ALIGN, _bodiesCount->y() + _bodiesCount->height() - 10);
	_bodyCountBox->resize( WIDGET_WIDTH - 18, 30 );
	_bodyCountBox->addItem( "2" );
	_bodyCountBox->addItem( "3" );
	_bodyCountBox->addItem( "4" );
	_bodyCountBox->setCurrentIndex( 0 );

	_startingDataLabel = new QLabel( tr( "Starting data" ), this );
	_startingDataLabel->move( LEFT_LEFT_ALIGN, _bodyCountBox->y() + _bodyCountBox->height() );
	_massLabel = new QLabel( tr( "Bodys\' mass [kg]" ), this );
	_massLabel->move( LEFT_ALIGN, _startingDataLabel->y() + _startingDataLabel->height() - PADDING );
	_massSlider = new QSlider( Qt::Horizontal, this );
	_massSlider->resize( SLIDER_SIZE );
	_massSlider->move( LEFT_ALIGN, _massLabel->y() + _massLabel->height() - 2*PADDING );
	_massSlider->setFocusPolicy( Qt::NoFocus );
	_massSlider->setRange( 1, 50 );
	_massSlider->setValue( 20 );
	connect( _massSlider, &QSlider::valueChanged, this, &WorkDock::changeMass );
	_massLabelNum = new QLabel( "0.2", this );
	_massLabelNum->resize( LABEL_NUM_WIDTH, _massLabelNum->height() );
	_massLabelNum->move( _massSlider->x() + _massSlider->width() + PADDING, _massSlider->y() - AFTER_SLDIER_PADDDING );

	_kLabel = new QLabel( tr( "Stiffness coefficient [N/m]" ), this );
	_kLabel->move( LEFT_ALIGN, _massSlider->y() + _massSlider->height() + PADDING );
	_kSlider = new QSlider( Qt::Horizontal, this );
	_kSlider->resize( SLIDER_SIZE );
	_kSlider->move( LEFT_ALIGN, _kLabel->y() + _kLabel->height() - 2*PADDING );
	_kSlider->setFocusPolicy( Qt::NoFocus );
	_kSlider->setRange( 25, 250 );
	connect( _kSlider, &QSlider::valueChanged, this, &WorkDock::changeK );
	_kLabelNum = new QLabel( "25", this );
	_kLabelNum->resize( LABEL_NUM_WIDTH, _kLabelNum->height() );
	_kLabelNum->move( _kSlider->x() + _kSlider->width() + PADDING, _kSlider->y() - AFTER_SLDIER_PADDDING );

	_xLabel.push_back( new QLabel( tr( "Starting shift of the 1st body [m]" ), this ) );
	_xLabel[0]->move( LEFT_ALIGN, (_kSlider->y() + _kSlider->height() + PADDING  ) );
	_xSlider.push_back( new QSlider( Qt::Horizontal, this ) );
	_xSlider[0]->resize( SLIDER_SIZE );
	_xSlider[0]->move( LEFT_ALIGN, _xLabel[0]->y() + _xLabel[0]->height() - 2*PADDING );
	_xSlider[0]->setFocusPolicy( Qt::NoFocus );
	_xSlider[0]->setRange( LEFT_SHIFT_BORDER, RIGHT_SHIFT_BORDER );
	connect( _xSlider[0], &QSlider::valueChanged, this, &WorkDock::changeShift1 );
	_xLabelNum.push_back( new QLabel( "0", this ) );
	_xLabelNum[0]->resize( LABEL_NUM_WIDTH, _xLabelNum[0]->height() );
	_xLabelNum[0]->move( _xSlider[0]->x() + _xSlider[0]->width() + PADDING, _xSlider[0]->y() - AFTER_SLDIER_PADDDING );

	_xLabel.push_back( new QLabel( tr( "Starting shift of the 2nd body [m]" ), this ) );
	_xLabel[1]->move( LEFT_ALIGN, _xSlider[0]->y() + _xSlider[0]->height() + PADDING );
	_xSlider.push_back( new QSlider( Qt::Horizontal, this ) );
	_xSlider[1]->resize( SLIDER_SIZE );
	_xSlider[1]->move( LEFT_ALIGN, _xLabel[1]->y() + _xLabel[1]->height() - 2*PADDING );
	_xSlider[1]->setFocusPolicy( Qt::NoFocus );
	_xSlider[1]->setRange( LEFT_SHIFT_BORDER, RIGHT_SHIFT_BORDER );
	connect( _xSlider[1], &QSlider::valueChanged, this, &WorkDock::changeShift2 );
	_xLabelNum.push_back( new QLabel( "0", this ) );
	_xLabelNum[1]->resize( LABEL_NUM_WIDTH, _xLabelNum[1]->height() );
	_xLabelNum[1]->move( _xSlider[1]->x() + _xSlider[1]->width() + PADDING, _xSlider[1]->y() - AFTER_SLDIER_PADDDING );


	_xLabel.push_back( new QLabel( tr( "Starting shift of the 3rd body [m]" ), this ) );
	_xLabel[2]->move( LEFT_ALIGN, _xSlider[1]->y() + _xSlider[1]->height() + PADDING );
	_xLabel[2]->hide();
	_xSlider.push_back( new QSlider( Qt::Horizontal, this ) );
	_xSlider[2]->resize( SLIDER_SIZE );
	_xSlider[2]->move( LEFT_ALIGN, _xLabel[2]->y() + _xLabel[2]->height() - 2*PADDING );
	_xSlider[2]->setFocusPolicy( Qt::NoFocus );
	_xSlider[2]->hide();
	_xSlider[2]->setRange( LEFT_SHIFT_BORDER, RIGHT_SHIFT_BORDER );
	connect( _xSlider[2], &QSlider::valueChanged, this, &WorkDock::changeShift3 );
	_xLabelNum.push_back( new QLabel( "0", this ) );
	_xLabelNum[2]->resize( LABEL_NUM_WIDTH, _xLabelNum[2]->height() );
	_xLabelNum[2]->move( _xSlider[2]->x() + _xSlider[2]->width() + PADDING, _xSlider[2]->y() - AFTER_SLDIER_PADDDING );
	_xLabelNum[2]->hide();

	_xLabel.push_back( new QLabel( tr( "Starting shift of the 4th body [m]" ), this ) );
	_xLabel[3]->move( LEFT_ALIGN, _xSlider[2]->y() + _xSlider[2]->height() + PADDING );
	_xLabel[3]->hide();
	_xSlider.push_back( new QSlider( Qt::Horizontal, this ) );
	_xSlider[3]->resize( SLIDER_SIZE );
	_xSlider[3]->move( LEFT_ALIGN, _xLabel[3]->y() + _xLabel[3]->height() - 2*PADDING );
	_xSlider[3]->setFocusPolicy( Qt::NoFocus );
	_xSlider[3]->setRange( LEFT_SHIFT_BORDER, RIGHT_SHIFT_BORDER );
	_xSlider[3]->hide();
	connect( _xSlider[3], &QSlider::valueChanged, this, &WorkDock::changeShift4 );
	_xLabelNum.push_back( new QLabel( "0", this ) );
	_xLabelNum[3]->resize( LABEL_NUM_WIDTH, _xLabelNum[3]->height() );
	_xLabelNum[3]->move( _xSlider[3]->x() + _xSlider[3]->width() + PADDING, _xSlider[3]->y() - AFTER_SLDIER_PADDDING );
	_xLabelNum[3]->hide();


	_timeLabel = new QLabel( tr( "Time [s]" ), this );
	_timeLabel->move( LEFT_LEFT_ALIGN, _xSlider[1]->y() + _xSlider[1]->height() + PADDING );
	_timerNumber = new QLCDNumber( this );
	_timerNumber->setDecMode();
	_timerNumber->setSegmentStyle(QLCDNumber::Flat);
	_timerNumber->resize( TIMER_SIZE );
	_timerNumber->move( _timeLabel->x(), _timeLabel->y() + _timeLabel->height() - 3*PADDING );

	_controlPanelLabel = new QLabel( tr( "Control panel" ), this );
	_controlPanelLabel->move( LEFT_LEFT_ALIGN, _timerNumber->y() + _timerNumber->height() );
	_speedLabel = new QLabel( tr( "Experiment speed [%]" ), this );
	_speedLabel->move( LEFT_ALIGN, _controlPanelLabel->y() + _controlPanelLabel->height() - 3*PADDING );
	_speedSlider = new QSlider( Qt::Horizontal, this );
	_speedSlider->resize( SLIDER_SIZE );
	_speedSlider->move( LEFT_ALIGN, _speedLabel->y() + _speedLabel->height() - 3*PADDING );
	_speedSlider->setFocusPolicy( Qt::NoFocus );
	_speedSlider->setRange( 10, 200 );
	_speedSlider->setSingleStep( 5 );
	_speedSlider->setValue( 100 );
	connect( _speedSlider, &QSlider::valueChanged, this, &WorkDock::changeSpeed );
	_speedLabelNum = new QLabel( "100", this );
	_speedLabelNum->resize( LABEL_NUM_WIDTH, _speedLabelNum->height() );
	_speedLabelNum->move( _speedSlider->x() + _speedSlider->width() + PADDING, _speedSlider->y() );

	_graphicsLabel = new QLabel( tr( "Graphics" ), this );
	_graphicsLabel->move( LEFT_ALIGN, _speedSlider->y() + _speedSlider->height() + PADDING );
	_graphicsSlider = new QSlider( Qt::Horizontal, this );
	_graphicsSlider->setFocusPolicy( Qt::NoFocus );
	_graphicsSlider->resize( SLIDER_SIZE );
	_graphicsSlider->move( LEFT_ALIGN, _graphicsLabel->y() + _graphicsLabel->height() - 3*PADDING );
	_graphicsSlider->setRange( 10, 100 );
	_graphicsSlider->setValue( 40 );
	connect( _graphicsSlider, &QSlider::valueChanged, this, &WorkDock::changeQuality );
	_graphicsSpeed = new QLabel( tr( "Speed" ), this );
	_graphicsSpeed->move( width() - LEFT_ALIGN - 50, _graphicsSlider->y() + _graphicsSlider->height() );
	_graphicsQuality = new QLabel( tr( "Quality" ), this );
	_graphicsQuality->move( LEFT_ALIGN, _graphicsSpeed->y() );

	_startButton = new QPushButton( tr( "Start" ), this );
	_startButton->resize( BUTTON_SIZE );
	_startButton->move( LEFT_LEFT_ALIGN, _graphicsQuality->y() + _graphicsQuality->height() + PART_PADDING );
	connect( _startButton, &QPushButton::released, this, &WorkDock::experimentStarts );
	_resetButton = new QPushButton( tr( "Reset" ), this );
	_resetButton->resize( BUTTON_SIZE );
	_resetButton->move( _startButton->x() + _startButton->width() + LEFT_LEFT_ALIGN, _startButton->y() );
	connect( _resetButton, &QPushButton::released, this, &WorkDock::experimentResets );

	_nstuLogoLabel = new QLabel( this );
	_nstuLogoLabel->setAlignment( Qt::AlignCenter );
	_nstuLogoLabel->setPixmap( QPixmap( ":/mres/NSTU_Logo.png" ) );
	_nstuLogoLabel->setMask( _nstuLogoLabel->pixmap()->mask() );
	_nstuLogoLabel->move( (width() - _nstuLogoLabel->pixmap()->width()) / 2, _resetButton->y() + _resetButton->height() + PART_PADDING );
	_yearLabel = new QLabel( tr( "Novosibirsk 2015" ), this );
	_yearLabel->resize( width(), _yearLabel->height() );
	_yearLabel->setAlignment( Qt::AlignCenter );
	_yearLabel->move( 0, _nstuLogoLabel->y() + _nstuLogoLabel->pixmap()->height() );

	// ========================================================================================
	// ======================== Connects' part ================================================
	// ========================================================================================

	connect( _bodyCountBox, SIGNAL( currentIndexChanged(int)), this, SIGNAL( stringsCountChanged(int) ) );
	connect( this, &WorkDock::stringsCountChanged, this, &WorkDock::changeLayoutsAndBodies );
}

WorkDock::~WorkDock()
{

}

void WorkDock::setTime( QString t )
{
	_timerNumber->display( t );
}

void WorkDock::changeLayoutsAndBodies( int bodiesCount )
{
	bodiesCount += 2;
	if ( bodiesCount > 4 )
		return;

	int n = theStorage.getNumOfSprings() - 1;
	if ( n == bodiesCount )
		return;

	switch ( bodiesCount ) {
		case 2:
		{
			switch ( n ) {
				case 3:
				{
					_xLabel[2]->hide();
					_xSlider[2]->hide();
					_xLabelNum[2]->hide();
					break;
				}
				case 4:
				{
					_xLabel[2]->hide();
					_xSlider[2]->hide();
					_xLabelNum[2]->hide();

					_xLabel[3]->hide();
					_xSlider[3]->hide();
					_xLabelNum[3]->hide();
					break;
				}
			}

			break;
		}
		case 3:
		{
			switch ( n ) {
				case 2:
				{
					_xLabel[2]->show();
					_xSlider[2]->show();
					_xLabelNum[2]->show();
					break;
				}
				case 4:
				{
					_xLabel[3]->hide();
					_xSlider[3]->hide();
					_xLabelNum[3]->hide();
					break;
				}
			}
			break;
		}
		case 4:
		{
			switch ( n ) {
				case 2:
				{
					_xLabel[2]->show();
					_xSlider[2]->show();
					_xLabelNum[2]->show();

					_xLabel[3]->show();
					_xSlider[3]->show();
					_xLabelNum[3]->show();
					break;
				}
				case 3:
				{
					_xLabel[3]->show();
					_xSlider[3]->show();
					_xLabelNum[3]->show();
					break;
				}
			}
			break;
		}
	}
	n = bodiesCount - 1;

	_timeLabel->move( 120, _xSlider[n]->y() + _xSlider[n]->height() + PADDING );
	_timerNumber->move( _timeLabel->x(), _timeLabel->y() + _timeLabel->height() - 3*PADDING );

	_controlPanelLabel->move( LEFT_LEFT_ALIGN, _timerNumber->y() + _timerNumber->height() );
	_speedLabel->move( LEFT_ALIGN, _controlPanelLabel->y() + _controlPanelLabel->height() - 3*PADDING );
	_speedSlider->move( LEFT_ALIGN, _speedLabel->y() + _speedLabel->height() - 3*PADDING );
	_speedLabelNum->move( _speedSlider->x() + _speedSlider->width() + PADDING, _speedSlider->y() );

	_graphicsLabel->move( LEFT_ALIGN, _speedSlider->y() + _speedSlider->height() + PADDING );
	_graphicsSlider->move( LEFT_ALIGN, _graphicsLabel->y() + _graphicsLabel->height() - 3*PADDING );
	_graphicsSpeed->move( width() - LEFT_ALIGN - 50, _graphicsSlider->y() + _graphicsSlider->height() );
	_graphicsQuality->move( LEFT_ALIGN, _graphicsSpeed->y() );
	_startButton->move( LEFT_LEFT_ALIGN, _graphicsQuality->y() + _graphicsQuality->height() + PART_PADDING );
	_resetButton->move( _startButton->x() + _startButton->width() + LEFT_LEFT_ALIGN, _startButton->y() );
	_nstuLogoLabel->move( (width() - _nstuLogoLabel->pixmap()->width()) / 2, _resetButton->y() + _resetButton->height() + PART_PADDING );
	_yearLabel->move( 0, _nstuLogoLabel->y() + _nstuLogoLabel->pixmap()->height() );

	if ( (theStorage.getNumOfSprings() - 1) != bodiesCount )
		emit needResize( bodiesCount - theStorage.getNumOfSprings() + 1 );

	theStorage.setNumOfSprings( bodiesCount + 1 );

	emit stringsCountChanged( bodiesCount + 1 );
}

void WorkDock::disableItems( bool dicision )
{
	// TODO
	_bodyCountBox->setDisabled( dicision );
	_massSlider->setDisabled( dicision );
	_kSlider->setDisabled( dicision );

	int n = theStorage.getNumOfSprings() - 1;
	for ( int i = 0; i < n; ++i ) {
		_xSlider[i]->setDisabled( dicision );
	}
}

void WorkDock::experimentStarts()
{
	if( !_started ) {
		disableItems( true );
		_started = true;
		_startButton->setText( tr( "Pause" ) );
		emit experimentStarted();
	}
	else {
		_started = false;
		_startButton->setText( tr( "Start" ) );
		emit experimentStopped();
	}
}

void WorkDock::experimentResets()
{
	// TODO: make all widgets to default values
	int n = theStorage.getNumOfSprings() - 1;
	for ( int i = 0; i < n; ++i )
		_xSlider[i]->setValue( 0 );

	_timerNumber->display( "0.00" );
	if ( _started ) {
		_started = false;
		_startButton->setText( tr( "Start" ) );
	}


	disableItems( false );
	emit experimentReset();
}

void WorkDock::changeMass( int weight )
{
	float w = weight * 0.01;
	_massLabelNum->setText( QString::number( w ) );
	emit massChanged( w );
}

void WorkDock::changeK( int k )
{
	_kLabelNum->setText( QString::number( k ) );
}

void WorkDock::changeShift1(int x)
{
	float _x = x * 0.01;
	_xLabelNum[0]->setText( QString::number( _x ) );
	emit shiftChanged( 0, _x );
}

void WorkDock::changeShift2(int x)
{
	float _x = x * 0.01;
	_xLabelNum[1]->setText( QString::number( _x ) );
	emit shiftChanged( 1, _x );
}

void WorkDock::changeShift3(int x)
{
	float _x = x * 0.01;
	_xLabelNum[2]->setText( QString::number( _x ) );
	emit shiftChanged( 2, _x );
}

void WorkDock::changeShift4(int x)
{
	float _x = x * 0.01;
	_xLabelNum[3]->setText( QString::number( _x ) );
	emit shiftChanged( 3, _x );
}

void WorkDock::changeSpeed( int speed )
{
	_speedLabelNum->setText( QString::number( speed ) );
	emit speedChanged( speed );
}

void WorkDock::changeQuality( int q )
{
	emit qualityChanged( q, _started );
}
