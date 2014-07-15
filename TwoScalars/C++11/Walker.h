#ifndef _Walker_
#define _Walker_

/*
* A single walker/trajectory beginning from the prior and compressing
* inwards in some direction.
*/

#include <vector>
#include <fstream>

template<class Type>
class Walker
{
	private:
		// Just a number that will get appended to the output files
		// from this walker.
		int identity;

		// Which scalar to ascend. Use -1 to get mixed directions
		int scalar;

		Type point;		
		std::vector<double> direction;
		std::vector<double> edge;
		std::vector<double> edge_tiebreakers;

		int iterations;

		// Write decisions (which way to compress)
		// to this file
		std::fstream choices_file;
		// Write values of scalars to this file
		std::fstream scalars_file;

		// Returns 'true' if the point 't' is above the
		// threshold as defined by 'edge' and 'edge_tiebreakers'
		bool is_okay(const Type& t);

	public:
		Walker(int identity, int scalar);
		~Walker();

		void initialise();
		bool advance(int steps);

		const Type& get_point() const { return point; }
};

// Function to create and launch a walker
template<class Type>
void launch_walker(int identity, int thin);

#include "WalkerImpl.h"

#endif

