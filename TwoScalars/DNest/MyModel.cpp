#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
:params(100)
,scalars(2)
{

}

void MyModel::fromPrior()
{
	for(size_t i=0; i<params.size(); i++)
		params[i] = randomU();

	compute_scalars();
}

double MyModel::perturb()
{
	int reps = (int)(pow(10., -3.*randomU())*params.size());
	if(reps == 0)
		reps = 1;
	if(reps == (int)params.size())
		reps = params.size();

	int which;
	for(int i=0; i<reps; i++)
	{
		which = randInt(params.size());
		params[which] += randh();
		params[which] = mod(params[which], 1.);
	}

	compute_scalars();

	return 0.;
}

void MyModel::compute_scalars()
{
	scalars[0] = 0.;
	for(size_t i=0; i<params.size(); i++)
		scalars[0] += -pow(params[i] - 0.5, 2);

	scalars[1] = 0.;
	for(size_t i=0; i<params.size(); i++)
		scalars[1] += -pow(sin(2.*M_PI*params[i]/0.5), 2);
}

double MyModel::logLikelihood() const
{
	return scalars[0];
}

void MyModel::print(std::ostream& out) const
{
	for(size_t i=0; i<params.size(); i++)
		out<<params[i]<<' ';
}

string MyModel::description() const
{
	return string("");
}

