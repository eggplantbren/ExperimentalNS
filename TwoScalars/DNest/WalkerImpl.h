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
	std::string filename2("scalars.txt");
	scalars_file.open(filename2.c_str(), std::ios::out);
}

template<class Type>
Walker<Type>::~Walker()
{
	scalars_file.close();
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
	int choice = DNest3::randInt(scalars.size());
	edge[choice] = scalars[choice];
	edge_tiebreakers[choice] = tiebreakers[choice];

	for(size_t i=0; i<scalars.size(); i++)
		scalars_file<<scalars[i]<<' '<<tiebreakers[i]<<' ';
	scalars_file<<std::endl;

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
	std::string filename("output.txt");

	Walker<Type> walker;
	walker.initialise();

	std::fstream fout(filename.c_str(), std::ios::out);
	for(int i=0; i<max_iterations; i++)
	{
		bool success = walker.advance(mcmc_steps);
		if(i%thin == 0)
		{
			walker.get_point().print(fout);
			fout<<std::endl;
		}
		if(!success)
			break;
	}
	fout.close();
}

