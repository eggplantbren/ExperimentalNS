#ifndef _Example_
#define _Example_

#include "Point.h"
#include <vector>
#include <ostream>

class Example:public Point
{
	private:
		std::vector<double> params;

		void compute_scalars();
	public:
		Example();
		void from_prior();
		double perturb();

	friend std::ostream& operator << (std::ostream& out, const Example& e);
};

#endif

