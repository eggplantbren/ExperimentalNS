#include "Walker.h"
#include "RNG.h"
#include <iostream>
#include <vector>

template<class Type>
Walker<Type>::Walker()
:direction(point.get_num_scalars())
,edge(point.get_num_scalars())
,edge_tiebreakers(point.get_num_scalars())
{
}

template<class Type>
void Walker<Type>::initialise()
{
	for(double& e : edge)
		e = -1E300;
	for(double& e : edge_tiebreakers)
		e = 0.;

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
	std::cout<<std::endl;
}

template<class Type>
void Walker<Type>::advance(int steps)
{
	int choice = RNG::randInt(direction);
	edge[choice] = point.get_scalars()[choice];
	edge_tiebreakers[choice] = point.get_tiebreakers()[choice];
}

