#pragma once

#include "MathLib/ap.h"
#include <vector>

#define theCalcs Calculations::getInsance()

typedef std::vector<double> vd;

class Calculations
{
public:
	static Calculations & getInsance();

	void calculateShifts( double t, vd & x );
	void calculateSpeed( double t, vd & v );
	void initializeCalculations( int n, int koefficient, float mass, vd & beginingShifts );
	void clear();

	inline bool isCleared() { return _cleared; }
	vd & getFrequency();

protected:
	Calculations();
	static Calculations * _calcs;

private:
	bool	_cleared;

	vd		_preAmplitudes;
	vd		_omega;
	vd		_phita;
	alglib::real_2d_array _sigma;

	void multip( alglib::real_2d_array & s, vd & b, vd & g );
	void calculateAmplitudes( vd & s, alglib::real_2d_array & s1, vd & h, int g );
};
