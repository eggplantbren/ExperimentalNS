#ifndef _Example_
#define _Example_

#include "Point.h"
#include <vector>

class Example:public Point
{
	private:
		std::vector<double> params;

		void compute_scalars();
	public:
		Example();
		void from_prior();
		double perturb();

};

#endif

