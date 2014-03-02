#include "Gravity.h"
#include "RNG.h"
#include "Utils.h"

#include <cmath>

using namespace std;

Gravity::Gravity()
:Point(2)
,x(1000), y(1000), z(1000), vx(1000), vy(1000), vz(1000)
,staleness(0)
{

}

void Gravity::from_prior()
{
	for(size_t i=0; i<x.size(); i++)
	{
		x[i] = -10. + 20.*RNG::rand();
		y[i] = -10. + 20.*RNG::rand();
		z[i] = -10. + 20.*RNG::rand();
		vx[i] = -10. + 20.*RNG::rand();
		vy[i] = -10. + 20.*RNG::rand();
		vz[i] = -10. + 20.*RNG::rand();
	}

	refresh();
	compute_scalars();
}

void Gravity::increment(int i, int sign)
{
	KE += sign*0.5*(vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i]);
	L += sign*(x[i]*vy[i] - y[i]*vx[i]);

	double rsq;
	for(size_t j=0; j<x.size(); j++)
	{
		if(i != static_cast<int>(j))
		{
			rsq = pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2)
				+ pow(z[i] - z[j], 2);
			if(rsq <= 0.01)
				rsq = 0.01;
			PE += -1./sqrt(rsq)*sign;
		}
	}
}

double Gravity::perturb()
{
	int reps = 1;
	if(RNG::rand() <= 0.5)
		reps += 1 + RNG::randInt(9);

	int which;
	for(int i=0; i<reps; i++)
	{
		which = RNG::randInt(x.size());

		// Remove effect of this particle
		increment(which, -1);

		x[which] += 20.*RNG::randh();
		x[which] = mod(x[which] + 10., 20.) - 10.;

		y[which] += 20.*RNG::randh();
		y[which] = mod(y[which] + 10., 20.) - 10.;

		z[which] += 20.*RNG::randh();
		z[which] = mod(z[which] + 10., 20.) - 10.;

		vx[which] += 20.*RNG::randh();
		vx[which] = mod(vx[which] + 10., 20.) - 10.;

		vy[which] += 20.*RNG::randh();
		vy[which] = mod(vy[which] + 10., 20.) - 10.;

		vz[which] += 20.*RNG::randh();
		vz[which] = mod(vz[which] + 10., 20.) - 10.;

		increment(which, +1);
	}

	staleness++;
	if(staleness >= 1000)
		refresh();

	compute_scalars();
	return 0.;
}

void Gravity::refresh()
{	
	KE = 0.; PE = 0.; L = 0.;
	for(size_t i=0; i<x.size(); i++)
		increment(i, 1);
	PE *= 0.5;
	staleness = 0;
}

void Gravity::compute_scalars()
{
	scalars[0] = -(KE + PE);
	scalars[1] = L;
}

ostream& operator << (ostream& out, const Gravity& e)
{
	for(double x : e.x)
		out<<x<<' ';
	for(double y : e.y)
		out<<y<<' ';
	for(double z : e.z)
		out<<z<<' ';
	for(double vx : e.vx)
		out<<vx<<' ';
	for(double vy : e.vy)
		out<<vy<<' ';
	for(double vz : e.vz)
		out<<vz<<' ';

	out<<e.staleness;
	return out;
}

