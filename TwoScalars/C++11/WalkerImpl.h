#include "Walker.h"
#include "RNG.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

template<class Type>
Walker<Type>::Walker(int identity)
:identity(identity)
,direction(point.get_num_scalars())
,edge(point.get_num_scalars())
,edge_tiebreakers(point.get_num_scalars())
,iterations(0)
{
	std::string filename("Output/choices");
	filename += std::to_string(identity);
	filename += std::string(".txt");

	std::cout<<filename<<std::endl;
	choices_file.open(filename.c_str(), std::ios::out);
}

template<class Type>
void Walker<Type>::initialise()
{
	for(double& e : edge)
		e = -1E300;
	for(double& e : edge_tiebreakers)
		e = 0.;

	// Choose a direction
	double total = 0.;
	for(double& d : direction)
	{
		d = exp(3*RNG::randn());
		total += d;
	}
	for(double& d : direction)
		d /= total;

	point.from_prior();
	point.from_prior_tiebreakers();

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
	int choice = RNG::randInt(direction);
	edge[choice] = point.get_scalars()[choice];
	edge_tiebreakers[choice] = point.get_tiebreakers()[choice];
	choices_file<<choice<<' '<<std::flush;

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

		if(is_okay(proposal) && RNG::rand() <= exp(logH))
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

// Function to create and launch a walker
template<class Type>
void launch_walker(int identity, int max_iterations, int mcmc_steps, int thin)
{
	std::string filename("Output/output");
	filename += std::to_string(identity);
	filename += std::string(".txt");

	Walker<Type> walker(identity);
	walker.initialise();

	std::fstream fout(filename.c_str(), std::ios::out);
	for(int i=0; i<max_iterations; i++)
	{
		bool success = walker.advance(mcmc_steps);
		if(i%thin == 0)
			fout<<std::setprecision(8)<<walker.get_point()<<std::endl;
		if(!success)
			break;
	}
	fout.close();
}

