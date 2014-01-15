#include "Example.h"
#include "RNG.h"
#include "Utils.h"

#include <cmath>

Example::Example()
:Point(2), params(1000)
{

}

void Example::from_prior()
{
	for(double& p : params)
		p = RNG::rand();
	compute_scalars();
}

double Example::perturb()
{
	int reps = 1;
	if(RNG::rand() <= 0.5)
		reps += 1 + RNG::randInt(9);


	int which;
	for(int i=0; i<reps; i++)
	{
		which = RNG::randInt(params.size());
		params[which] += RNG::randh();
		params[which] = mod(params[which], 1.);
	}

	compute_scalars();
	return 0.;
}

void Example::compute_scalars()
{
	scalars[0] = 0.;
	for(double x : params)
		scalars[0] += -pow(x - 0.5, 2);

	scalars[1] = 0.;
	for(double x : params)
		scalars[1] += -pow(sin(2.*M_PI*x/0.5), 2);
}

