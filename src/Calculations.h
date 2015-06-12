#pragma once

#include "MathLib/ap.h"
#include <vector>

typedef std::vector<double> vd;

class Calculations
{
public:
	Calculations();

	void calculateShifts( double t, vd & x );
	void initializeCalculations( int n, int koefficient, float mass, vd & beginingShifts );

private:
	vd _preAmplitudes;
	vd _omega;
	vd _phita;
	alglib::real_2d_array _sigma;

	void multip( alglib::real_2d_array & s, vd & b, vd & g );
	void calculateAmplitudes( vd & s, alglib::real_2d_array & s1, vd & h, int g );
};
