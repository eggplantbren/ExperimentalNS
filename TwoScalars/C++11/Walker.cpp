#include "Walker.h"
#include "RNG.h"
#include <iostream>

template<class Type>
Walker<Type>::Walker()
:direction(point.get_scalars().size())
{

}

template<class Type>
void Walker<Type>::initialise()
{
	// Choose direction from a dirichlet(1,...,1) distribution
	double total = 0.;
	for(double& d : direction)
	{
		d = -log(RNG::rand());
		total += d;
	}
	for(double& d : direction)
		d /= total;

	point.from_prior();
	point.from_prior_tiebreakers();

	std::cout<<"# Initialised a walker with direction: ";
	for(double d : direction)
		std::cout<<d<<"   ";
}

