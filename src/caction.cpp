#include "caction.h"

Caction::Caction()
{
    x = A0;
}

Caction::~Caction()
{

}

void Caction::InitBall()
{
	fita =		0;
	w0 =		sqrt( k / m );
	sigma =		r / (2 * m);
	w =			w0;
	T =			2 * pi1 * w0;
	AtimeT =	A0 * cos(w * T + fita);
	ldekrem =	log(A0 / AtimeT);
	oldx =		A0;
	oldtime =	-1;
	v =			0;
	E0 =		k * A0 * A0 / 2;
	E =			E0;
}

void Caction::Refresh( double Ntime )
{
    double t = Ntime / 1000.0;
		x = A0 * cos( w * t + fita );
        v = (x - oldx) / (t - oldtime);
        oldx = x;
        oldtime = t;       
}
