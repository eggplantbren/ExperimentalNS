#ifndef _MyModel_
#define _MyModel_

#include "Model.h"
#include <vector>

class MyModel:public DNest3::Model
{
	private:
		std::vector<double> params;
		std::vector<double> scalars;

		void compute_scalars();

	public:
		MyModel();

		// Getter for scalars
		const std::vector<double>& get_scalars() const
		{ return scalars; }

		// Number of scalars
		int get_num_scalars() const
		{ return static_cast<int>(scalars.size()); }

		// Generate the point from the prior
		void fromPrior();

		// Metropolis-Hastings proposals
		double perturb();

		// Likelihood function
		double logLikelihood() const;

		// Print to stream
		void print(std::ostream& out) const;

		// Return string with column information
		std::string description() const;
};

#endif

