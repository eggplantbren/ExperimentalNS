#include "Example.h"
#include "RNG.h"

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

