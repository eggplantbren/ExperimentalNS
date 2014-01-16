#ifndef _Walker_
#define _Walker_

/*
* A single walker/trajectory beginning from the prior and compressing
* inwards in some direction.
*/

#include <vector>

template<class Type>
class Walker
{
	private:
		Type point;		
		std::vector<double> direction;
		std::vector<double> edge;
		std::vector<double> edge_tiebreakers;

		int iterations;

		// Returns 'true' if the point 't' is above the
		// threshold as defined by 'edge' and 'edge_tiebreakers'
		bool is_okay(const Type& t);

	public:
		Walker();

		void initialise();
		bool advance(int steps);

		const Type& get_point() const { return point; }
};

#include "WalkerImpl.h"

#endif

