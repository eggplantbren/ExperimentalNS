#include "Walker.h"
#include "RNG.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

template<class Type>
Walker<Type>::Walker(int identity, int scalar)
:identity(identity)
,scalar(scalar)
,direction(point.get_num_scalars())
,edge(point.get_num_scalars())
,edge_tiebreakers(point.get_num_scalars())
,iterations(0)
{
	std::string filename1("Output/choices");
	filename1 += std::to_string(identity);
	filename1 += std::string(".txt");

	choices_file.open(filename1.c_str(), std::ios::out);

	std::string filename2("Output/scalars");
	filename2 += std::to_string(identity);
	filename2 += std::string(".txt");

	scalars_file.open(filename2.c_str(), std::ios::out);
}

template<class Type>
Walker<Type>::~Walker()
{
	choices_file.close();
	scalars_file.close();
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

	// Forget the direction if we've been told which scalar to use.
	if(scalar != -1)
	{
		direction.assign(direction.size(), 0.);
		direction[scalar] = 1.;
	}

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
	const std::vector<double>& scalars = point.get_scalars();
	int choice = RNG::randInt(direction);
	edge[choice] = scalars[choice];
	edge_tiebreakers[choice] = point.get_tiebreakers()[choice];

	choices_file<<choice<<' '<<std::flush;
	for(size_t i=0; i<scalars.size(); i++)
		scalars_file<<scalars[i]<<' ';
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

	Walker<Type> walker(identity, -1);
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

