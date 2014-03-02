#ifndef _Gravity_
#define _Gravity_

#include "Point.h"
#include <vector>
#include <ostream>

class Gravity:public Point
{
	private:
		std::vector<double> x, y, z, vx, vy, vz;

		long double PE, KE, L;
		int staleness;

		void refresh();
		void increment(int i, int sign);
		void compute_scalars();
	public:
		Gravity();
		void from_prior();
		double perturb();

	friend std::ostream& operator << (std::ostream& out, const Gravity& e);
};

#endif

