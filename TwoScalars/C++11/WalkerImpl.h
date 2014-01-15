#include "Walker.h"
#include "RNG.h"
#include <iostream>
#include <vector>

template<class Type>
Walker<Type>::Walker()
:direction(point.get_num_scalars())
,edge(point.get_num_scalars())
,edge_tiebreakers(point.get_num_scalars())
,iterations(0)
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

	std::cout<<"# Edge "<<(iterations + 1)<<": (";
	for(size_t i=0; i<edge.size(); i++)
	{
		std::cout<<edge[i];
		if((i+1) != edge.size())
			std::cout<<", ";
	}
	std::cout<<"). Exploring..."<<std::flush;

	Type proposal;
	for(int i=0; i<steps; i++)
	{
		proposal = point;
		double logH = proposal.perturb();

		if(is_okay(proposal) && RNG::rand() <= exp(logH))
			point = proposal;
	}

	std::cout<<"done."<<std::endl;
	iterations++;
}

template<class Type>
bool Walker<Type>::is_okay(const Type& t)
{
	const std::vector<double>& scalars = t.get_scalars();
	const std::vector<double>& tiebreakers = t.get_tiebreakers();

	bool result = true;
	for(size_t i=0; i<scalars.size(); i++)
	{
		if(scalars[i] < edge[i] ||
			(scalars[i] == edge[i] &&
				tiebreakers[i] < edge_tiebreakers[i]))
		{
			result = false;
			break;
		}
	}

	return result;
}

