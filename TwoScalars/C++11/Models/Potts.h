#ifndef _Potts_
#define _Potts_

#include "Point.h"
#include <vector>
#include <ostream>

class Potts:public Point
{
	private:
		static const int num_colors = 5;

		std::vector< std::vector<int> > x;

		// So we can just update on the fly
		int score;
		int score2;

		void compute_score();
		void compute_scalars();
	public:
		Potts();
		void from_prior();
		double perturb();

	friend std::ostream& operator << (std::ostream& out, const Potts& e);
};

#endif

