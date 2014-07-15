#ifndef _Walker_
#define _Walker_

/*
* A single walker/trajectory beginning from the prior and compressing
* inwards in some direction chosen anew at each iteration.
*/

#include <vector>
#include <fstream>

template<class Type>
class Walker
{
	private:
		Type point;

		// Tiebreakers for all scalars (don't use DNest tiebreaker)
		std::vector<double> tiebreakers;
		std::vector<double> direction;
		std::vector<double> edge;
		std::vector<double> edge_tiebreakers;

		int iterations;

		// Write values of scalars to this file
		std::fstream scalars_file;

		// Returns 'true' if the point 't' is above the
		// threshold as defined by 'edge' and 'edge_tiebreakers'
		bool is_okay(const Type& t);

	public:
		Walker();

		void initialise();
		bool advance(int steps);

		const Type& get_point() const { return point; }
		const std::vector<double>& get_tiebreakers() const
		{ return tiebreakers; }
};

// Function to create and launch a walker
template<class Type>
void launch_walker(int max_iterations, int mcmc_steps, int thin);

#include "WalkerImpl.h"

#endif

