#include "Point.h"
#include "RNG.h"
#include "Utils.h"

using namespace std;

Point::Point(int num_scalars)
:num_scalars(num_scalars), scalars(num_scalars), tiebreakers(num_scalars)
{

}

void Point::from_prior_tiebreakers()
{
	for(double& t : tiebreakers)
		t = RNG::rand();
}

void Point::perturb_tiebreakers()
{
	int which = RNG::randInt(tiebreakers.size());
	tiebreakers[which] += RNG::randh();
	tiebreakers[which] = mod(tiebreakers[which], 1.);
}

