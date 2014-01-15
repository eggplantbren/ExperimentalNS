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

	public:
		Walker();

		void initialise();

};

#include "WalkerImpl.h"

#endif

