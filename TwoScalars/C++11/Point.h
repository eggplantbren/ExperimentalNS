#ifndef _Point_
#define _Point_

#include <vector>

/*
* Abstract class defining what is needed to implement a model.
* This will be like DNest. An object of a subclass represents a
* point in parameter space.
*/

class Point
{
	protected:
		int num_scalars;
		std::vector<double> scalars;
		std::vector<double> tiebreakers;

	public:
		// Pass in the number of scalars
		Point(int num_scalars);

		// Generate the point from the prior
		virtual void from_prior() = 0;

		// Do a Metropolis-Hastings proposal that satisfies detailed
		// balance wrt the prior. Return log of any ratios needed to
		// achieve this.
		virtual double perturb() = 0;

		// Obligatory methods for tiebreakers
		void from_prior_tiebreakers();
		void perturb_tiebreakers();

		// Getters for scalars and tiebreakers
		int get_num_scalars() const { return num_scalars; }
		const std::vector<double>& get_scalars() const
		{
			return scalars;
		}
		const std::vector<double>& get_tiebreakers() const
		{
			return tiebreakers;
		}
};

#endif

