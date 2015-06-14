#include "Plot.h"

#include "Calculations.h"
#include "Storage.h"

#include <QtCore/QtMath>

#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>

#include <QtWidgets/QLabel>

#include <algorithm>

typedef std::vector<vd> vvd;

Graph::Graph( QWidget * parent, const QString & dependenceType ):
	QWidget( nullptr )
{
	setAttribute( Qt::WA_DeleteOnClose );

	if ( theCalcs.isCleared() ) {
		setWindowTitle( tr( "Error" ) );
		resize( 400, 178 );
		QLabel * oops = new QLabel( tr( "Oops!" ), this );
		oops->resize( 400, oops->height() );
		oops->move( 0, 40 );
		oops->setAlignment( Qt::AlignCenter );

		QLabel * next = new QLabel( tr ( "Data is underfined." ), this );
		next->resize( 400, next->height() );
		next->move( 0, 70 );
		next->setAlignment( Qt::AlignCenter );

		QLabel * pl = new QLabel( tr( "Please, run the experiment." ), this );
		pl->resize( 400, pl->height() );
		pl->move( 0, 100 );
		pl->setAlignment( Qt::AlignCenter );

		setStyleSheet( "QLabel { font: 18px bold; }" );
		_dataDefined = false;

		move( parent->x() + (parent->width() - width()) / 2 , parent->y() + (parent->height() - height()) / 2 );

		return;
	}
	_dataDefined = true;
	setFixedSize( 805, 600 );



	vd omegas = theCalcs.getFrequency();
	for ( uint i = 0; i < omegas.size(); ++i )
		omegas[i] = pow( omegas[i], -1 );
	double maxFreq = *std::max_element( omegas.begin(), omegas.end() );
	_period =  2 * M_PI * maxFreq * 4;
	_countOfFuncPoints = ceil( _period * 140 );
	double step = _period / _countOfFuncPoints;
	_gridStepX =_period  / 20.0;
	int countOfBodies = theStorage.getNumOfSprings() - 1;

	int i;
	double time = 0;
	int j;
	double currMax = 0;
	double currMin = 0;
	double dataYMax = 0;
	double dataYMin = 0;
	_depX = "t";
	if ( !QString::compare( dependenceType, "xt") || !QString::compare( dependenceType, "vx" ) ) {
		setWindowTitle( tr( "Plots dependence X from t" ) );

		_X.resize( countOfBodies, vd( _countOfFuncPoints, 0 ) );
		_depY = "X";
		for ( i = 0; i < _countOfFuncPoints; ++i ) {
			vd stepX( countOfBodies, 0 );
			theCalcs.calculateShifts( time, stepX );
			for ( j = 0; j < countOfBodies; ++j )
				_X[j][i] = stepX[countOfBodies - j - 1] ;
			time += step;

			currMax = *std::max_element( stepX.begin(), stepX.end() );
			if ( currMax > dataYMax )
				dataYMax = currMax;
			currMin = *std::min_element( stepX.begin(), stepX.end() );
			if ( currMin < dataYMin )
				dataYMin = currMin;
		}
		dataYMax = std::max( dataYMax, qAbs( dataYMin ) );
		for ( i = 0; i < _countOfFuncPoints; ++i )
			for ( j = 0; j < countOfBodies; ++j )
				_X[j][i] /= dataYMax;
		if ( !QString::compare( dependenceType, "vx" ) )
			_gridStepX = dataYMax / 10.0 ;
		else
			_gridStepY = dataYMax / 10.0 ;
	}
	if ( !QString::compare( dependenceType, "vt" ) || !QString::compare( dependenceType, "vx" ) ) {
		setWindowTitle( tr( "Plots dependence V from t" ) );
		_V.resize( countOfBodies, vd( _countOfFuncPoints, 0 ) );
		_depY = "V";
		for ( i = 0; i < _countOfFuncPoints; ++i ) {
			vd stepV( countOfBodies, 0 );
			theCalcs.calculateSpeed( time, stepV );
			for ( j = 0; j < countOfBodies; ++j )
				_V[j][i] = stepV[j];
			time += step;

			currMax = *std::max_element( stepV.begin(), stepV.end() );
			if ( currMax > dataYMax )
				dataYMax = currMax;
			currMin = *std::min_element( stepV.begin(), stepV.end() );
			if ( currMin < dataYMin )
				dataYMin = currMin;
		}
		dataYMax = std::max( dataYMax, qAbs( dataYMin ) );
		for ( i = 0; i < _countOfFuncPoints; ++i )
			for ( j = 0; j < countOfBodies; ++j )
				_V[j][i] /= dataYMax;
		_gridStepY = dataYMax / 10.0;
	}
	if ( !QString::compare( dependenceType, "vx" ) ) {
		setWindowTitle( tr( "Plots dependence V from X" ) );
		_depX = "X";
		_depY = "V";
	}
}

Graph::~Graph()
{

}

void Graph::paintEvent( QPaintEvent * event )
{
	QPainter painter( this );
	painter.fillRect( event->rect(), Qt::white );
	if ( !_dataDefined )
		return;

	QPen pen;
	QBrush brush;
	brush.setStyle( Qt::NoBrush );
	painter.setBrush( brush );

	const int LEFT_PADDING = 50;
	const int RIGHT_PADDING = 20;
	const int TOP_PADDING = 20;
	const int HALF_Y = 11;
	const int WIDTH = 800;

	QPointF pt1, pt2;

	// drawing drawing grid
	pen.setColor( Qt::lightGray );
	pen.setWidth( 1 );
	painter.setPen( pen );

	int i;
	pt1.setX( LEFT_PADDING );
	pt2.setX( WIDTH - RIGHT_PADDING );
	int mid = (TOP_PADDING + 500) / 2;
	double yStep = mid / HALF_Y;
	for ( i = 1; i < HALF_Y; ++i ) {
		pt1.setY( mid - i * yStep );
		pt2.setY( pt1.y() );
		painter.drawLine( pt1, pt2 );

		pt1.setY( mid + i * yStep );
		pt2.setY( pt1.y() );
		painter.drawLine( pt1, pt2 );
	}

	pt1.setY( TOP_PADDING );
	pt2.setY( 500 );
	double xStep = (WIDTH - LEFT_PADDING - RIGHT_PADDING) / 20;
	const int FULL_X = 21;
	for ( i = 1; i < FULL_X; ++i ) {
		pt1.setX( LEFT_PADDING + i * xStep );
		pt2.setX( pt1.x() );
		painter.drawLine( pt1, pt2 );
	}

	// drawing axis ( and arrows? )
	pen.setColor( Qt::black );
	pen.setWidth( 2 );
	painter.setPen( pen );

	pt1.setX( LEFT_PADDING );
	pt1.setY( TOP_PADDING );
	pt2.setX( LEFT_PADDING );
	pt2.setY( 500 );
	painter.drawLine( pt1, pt2 );

	pt1.setY( (500 + TOP_PADDING) / 2 );
	pt2.setX( WIDTH - RIGHT_PADDING - 1 );
	pt2.setY( pt1.y() );
	painter.drawLine( pt1, pt2 );

	// drawing strings
	pt1.setX( LEFT_PADDING - 5 );
	pt1.setY( TOP_PADDING - 7 );
	QFont font;
	font.setPixelSize( 15 );
	painter.setFont( font );
	painter.drawText( pt1, _depY );

	pt1.setX( WIDTH - RIGHT_PADDING + 3 );
	pt1.setY( mid - 1 );
	painter.drawText( pt1, _depX );

	const int PADDING_TEXT = 6;
	pt1.setX( PADDING_TEXT );
	painter.drawText( QPoint( PADDING_TEXT, mid + PADDING_TEXT ), "0" );
	for ( i = 1; i < HALF_Y; ++i ) {
		pt1.setY( mid - i * (mid / HALF_Y) + PADDING_TEXT );
		painter.drawText( pt1, QString::number( i * _gridStepY, 'f', 2 ) );

		pt1.setY( mid + i * (mid / HALF_Y) + PADDING_TEXT );
		painter.drawText( pt1, QString::number( -i * _gridStepY, 'f', 2 ) );
	}

	pt1.setY( mid + 13 );
	for ( i = 1; i < FULL_X; ++i ) {
		if ( i % 2 ) {
			pt1.setX( RIGHT_PADDING + i * xStep + 18 );
			painter.drawText( pt1, QString::number( i * _gridStepX, 'f', 2 ) );
		}
	}

	// drawing graphics
	std::vector<QColor> colors;
	colors.push_back( QColor( Qt::blue ) );
	colors.push_back( QColor( Qt::green ) );
	colors.push_back( QColor( Qt::red ) );
	colors.push_back( QColor( Qt::magenta) );
	pen.setWidth( 3 );
	int n = theStorage.getNumOfSprings() - 1;
	int j;
	const int MAX_Y = yStep * 10;
	painter.setRenderHint( QPainter::Antialiasing );
	double timeStep = ((double)( WIDTH - RIGHT_PADDING - LEFT_PADDING )) / _countOfFuncPoints;

	if ( !QString::compare( _depY, "X" ) ) {
		for ( j = 0; j < n; ++j ) {
			pen.setColor( colors[j] );
			painter.setPen( pen );
			pt2.setX( LEFT_PADDING );
			pt2.setY( mid + _X[j][0] * MAX_Y );
			for ( i = 1; i < _countOfFuncPoints; ++i ) {
				pt1 = pt2;
				pt2.setX( LEFT_PADDING + timeStep * i );
				pt2.setY( mid + _X[j][i] * MAX_Y );
				painter.drawLine( pt1, pt2 );
			}
		}
	}
	else if ( !QString::compare( _depX, "t" ) ) {
		for ( j = 0; j < n; ++j ) {
			pen.setColor( colors[j] );
			painter.setPen( pen );
			pt2.setX( LEFT_PADDING );
			pt2.setY( mid + _V[j][0] * MAX_Y );
			for ( i = 1; i < _countOfFuncPoints; ++i ) {
				pt1 = pt2;
				pt2.setX( LEFT_PADDING + timeStep * i );
				pt2.setY( mid + _V[j][i] * MAX_Y );
				painter.drawLine( pt1, pt2 );
			}
		}
	}
	else {
		for ( j = 0; j < n; ++j ) {
			pen.setColor( colors[j] );
			painter.setPen( pen );
			pt2.setX( LEFT_PADDING );
			pt2.setY( mid + _V[j][0] * MAX_Y );
			for ( i = 1; i < _countOfFuncPoints; ++i ) {
				pt1 = pt2;
				pt2.setX( LEFT_PADDING + timeStep * i );
				pt2.setY( mid + _V[j][i] * MAX_Y );
				painter.drawLine( pt1, pt2 );
			}
		}
	}

	// drawing table of colors
}

