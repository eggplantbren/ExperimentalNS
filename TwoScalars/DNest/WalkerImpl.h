#include "Walker.h"
#include <RandomNumberGenerator.h>
#include <Utils.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

template<class Type>
Walker<Type>::Walker()
:tiebreakers(point.get_num_scalars())
,direction(point.get_num_scalars())
,edge(point.get_num_scalars())
,edge_tiebreakers(point.get_num_scalars())
,iterations(0)
{
}

template<class Type>
void Walker<Type>::initialise()
{
	for(int i=0; i<point.get_num_scalars(); i++)
	{
		edge[i] = -1E300;
		edge_tiebreakers[i] = 0.;
	}

	// Choose a direction
	double total = 0.;
	for(size_t i=0; i<direction.size(); i++)
	{
		direction[i] = exp(3*DNest3::randn());
		total += direction[i];
	}
	for(size_t i=0; i<direction.size(); i++)
		direction[i] /= total;

	point.fromPrior();
	for(size_t i=0; i<tiebreakers.size(); i++)
		tiebreakers[i] = DNest3::randomU();

	std::cout<<"# Initialised a walker with direction (";
	for(size_t i=0; i<direction.size(); i++)
	{
		std::cout<<direction[i];
		if((i+1) != direction.size())
			std::cout<<", ";
	}
	std::cout<<")."<<std::endl;
	std::cout<<"# Edge 0: (";
	for(size_t i=0; i<edge.size(); i++)
	{
		std::cout<<edge[i];
		if((i+1) != edge.size())
			std::cout<<", ";
	}
	std::cout<<")."<<std::endl;
}

template<class Type>
bool Walker<Type>::advance(int steps)
{
	const std::vector<double>& scalars = point.get_scalars();
	int choice;
	do
	{
 		choice = DNest3::randInt(scalars.size());
	}while(DNest3::randomU() > direction[choice]);
	edge[choice] = scalars[choice];
	edge_tiebreakers[choice] = tiebreakers[choice];

	std::cout<<"# Edge "<<(iterations + 1)<<": (";
	for(size_t i=0; i<edge.size(); i++)
	{
		std::cout<<edge[i];
		if((i+1) != edge.size())
			std::cout<<", ";
	}
	std::cout<<"). Exploring..."<<std::flush;

	int accepts = 0;
	Type proposal;
	for(int i=0; i<steps; i++)
	{
		proposal = point;
		double logH = proposal.perturb();

		// Perturb tiebreakers
		int which = DNest3::randInt(tiebreakers.size());
		tiebreakers[which] += DNest3::randh();
		tiebreakers[which] = DNest3::mod(tiebreakers[which], 1.);

		if(is_okay(proposal) && DNest3::randomU() <= exp(logH))
		{
			point = proposal;
			accepts++;
		}
	}

	std::cout<<"done. Accepted "<<accepts<<"/"<<steps<<"."<<std::endl;
	if(static_cast<double>(accepts)/steps < 0.02)
		return false;
	iterations++;

	return true;
}

template<class Type>
bool Walker<Type>::is_okay(const Type& t)
{
	const std::vector<double>& scalars = t.get_scalars();

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

// Function to create and launch a walker
template<class Type>
void launch_walker(int max_iterations, int mcmc_steps, int thin)
{
	Walker<Type> walker;
	walker.initialise();

	std::fstream fout("output.txt", std::ios::out|std::ios::app);
	std::fstream fout2("scalars.txt", std::ios::out|std::ios::app);
	for(int i=0; i<max_iterations; i++)
	{
		bool success = walker.advance(mcmc_steps);
		if(i%thin == 0)
		{
			walker.get_point().print(fout);
			fout<<std::endl;

			std::vector<double> scalars = walker.get_point().get_scalars();
			std::vector<double> tiebreakers = walker.get_tiebreakers();
			for(size_t i=0; i<scalars.size(); i++)
				fout2<<scalars[i]<<' '<<tiebreakers[i]<<' ';
			fout2<<std::endl;
		}
		if(!success)
			break;
	}
	fout.close();
	fout2.close();
}

