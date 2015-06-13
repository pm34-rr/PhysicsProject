#include "Calculations.h"

#include "MathLib/linalg.h"

typedef std::vector<std::vector<double> > vvd;

Calculations * Calculations::_calcs = nullptr;

Calculations::Calculations()
{
	_cleared = true;
}

Calculations &Calculations::getInsance()
{
	if ( _calcs == nullptr )
		_calcs = new Calculations;

	return *_calcs;
}

void Calculations::calculateShifts( double t, vd & x )
{
	int i, j;
	int n = _preAmplitudes.size();

	vd amplitude( n, 0 );
	for ( int i = 0; i < n; ++i )
		x[i] = 0;
	for ( i = 0; i < n; ++i ) {
		calculateAmplitudes( _preAmplitudes, _sigma, amplitude, i );
		for ( j = 0; j < n; ++j )
			x[j] += amplitude[j] * cos( _omega[i]*t + _phita[i] );
	}

	vd temp( n, 0 );
	for ( int i = 0; i < n; ++i ) {
		temp[i] = x[ n - i - 1];
	}
	for ( int i = 0; i < n; ++i )
		x[i] = temp[i];
}

void Calculations::calculateSpeed( double t, vd & v )
{
	int i, j;
	int n = _preAmplitudes.size();

	vd amplitude( n, 0 );
	for ( int i = 0; i < n; ++i )
		v[i] = 0;
	for ( i = 0; i < n; ++i ) {
		calculateAmplitudes( _preAmplitudes, _sigma, amplitude, i );
		for ( j = 0; j < n; ++j )
			v[j] -= amplitude[j] * _omega[i] * sin( _omega[i]*t + _phita[i] );
	}
}

void Calculations::initializeCalculations( int n, int koefficient, float mass, vd & beginingShifts )
{
	// swapping
	_cleared = false;
	vd temp( n, 0 );
	for ( int i = 0; i < n; ++i ) {
		temp[i] = beginingShifts[ n - i - 1];
	}
	for ( int i = 0; i < n; ++i )
		beginingShifts[i] = temp[i];

	alglib::real_2d_array OMEGA, Sigma1, VR, SigmaV, SigmaV1;
	alglib::real_1d_array Teta, WI;
	Teta.setlength( n );
	SigmaV.setlength( n, n );
	SigmaV1.setlength( n, n );
	Sigma1.setlength( n, n );
	WI.setlength( n );
	OMEGA.setlength( n, n );
	_sigma.setlength( n, n );
	VR.setlength( n, n );

	vd m( n, mass );
	vd k( n+1, koefficient );
	vvd omega( n+1, vd(n, 0) );

	int i, j;
	for ( i = 0; i < n + 1; ++i )
		for ( j = 0; j < n; ++j )
			omega[i][j] = k[i] / m[j];

	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j )
			OMEGA[i][j] = 0;

	for ( i = 0; i < n; ++i) {
		if ( i == 0 ) {
			OMEGA[i][i] = omega[0][0] + omega[1][0];
			OMEGA[0][1] = -omega[1][0];
		}
		else if ( i > 0 ) {
			if ( i < n-1 ) {
				OMEGA[i][i - 1] = -omega[i][i];
				OMEGA[i][i] = omega[i][i] + omega[i + 1][i];
				OMEGA[i][i + 1] = -omega[i + 1][i];
			}
			else {
				OMEGA[i][i - 1] = -omega[i][i];
				OMEGA[i][i] = omega[i][i] + omega[i + 1][i];
			}
		}
	}
	alglib::rmatrixevd( OMEGA, n, 3, Teta, WI, VR, _sigma );
	double sum;
	// normalize
	for ( j = 0; j < n; ++j ) {
		sum = 0;
		for ( i = 0; i < n; ++i )
			sum += _sigma[i][j] * _sigma[i][j];
		for ( i = 0; i < n; ++i )
			_sigma[i][j] /= sqrt( sum );
	}

	_omega.resize( n, 0 );
	for ( i = 0; i < n; ++i ) {
		Teta[i] = sqrt( Teta[i] );
		_omega[i] = Teta[i];
	}

	for ( i = 0; i < n; ++i )
		for( j = 0; j < n; ++j )
			SigmaV[j][i] = -Teta[i] * _sigma(j, i);

	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j ) {
			Sigma1[i][j] = _sigma[i][j];
			SigmaV1[i][j] = SigmaV[i][j];
		}

	alglib::matinvreport rep;
	alglib::ae_int_t g;
	alglib::rmatrixinverse( Sigma1, g, rep );
	alglib::rmatrixinverse( SigmaV1, g, rep );
	vd C1( n, 0 );
	vd C2( n, 0 );
	vd V0( n, 0 );
	multip( Sigma1, beginingShifts, C1 );
	multip( SigmaV1, V0, C2 );

	_preAmplitudes.resize( n, 0 );
	for ( i = 0; i < n; ++i )
		_preAmplitudes[i] = sqrt( C1[i] * C1[i] + C2[i] * C2[i] );

	_phita.resize( n, 0 );
	for ( i = 0; i < n; ++i ) {
		if ( _preAmplitudes[i] == 0 )
			_phita[i] = 0;
		else {
			_phita[i] = atan( C2[i] / C1[i] );
			int ex = C1[i] * 1000;
			if ( ex < 0 )
				_phita[i] += M_PI ;
			else if ( ex > 0 ) {
				int ex2 = C2[i] * 1000;
				if ( ex2 < 0 )
					_phita[i] += 2 * M_PI;
			}
		}
	}
	// swapping
	for ( int i = 0; i < n; ++i ) {
		temp[i] = beginingShifts[ n - i - 1];
	}
	for ( int i = 0; i < n; ++i )
		beginingShifts[i] = temp[i];
}

void Calculations::clear()
{
	_preAmplitudes.clear();
	_omega.clear();
	_phita.clear();
	_sigma.setlength( 0, 0 );
	_cleared = true;
}

vd & Calculations::getFrequency()
{
	return _omega;
}

void Calculations::multip( alglib::real_2d_array & s, vd & b, vd & g )
{
	int i, j;
	int n = b.size();
	for ( j = 0; j < n; ++j )
		for ( i = 0; i < n; ++i )
			g[j] += b[i] * s[j][i];
}

void Calculations::calculateAmplitudes( vd & s, alglib::real_2d_array & s1, vd & h, int g )
{
	int n = s.size();
	for (int i = 0; i < n; i++)
		h[i] = s[g] * s1[i][g];
}
