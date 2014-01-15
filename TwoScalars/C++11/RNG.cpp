#include "RNG.h"

using namespace std;

// Define the engine and the distributions
mt19937 RNG::engine;
uniform_real_distribution<> RNG::uniform(0., 1.);
normal_distribution<> RNG::normal(0., 1.);

void RNG::seed(unsigned long value)
{
	engine.seed(value);
}

double RNG::rand()
{
	return uniform(engine);	
}

double RNG::randn()
{
	return normal(engine);	
}

