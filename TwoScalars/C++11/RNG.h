#ifndef _RNG_
#define _RNG_

#include <random>

// Singleton class wrapping C++11's random number generators
class RNG
{
	private:
		// The engine
		static std::mt19937 engine;

		// Distributions
		static std::uniform_real_distribution<> uniform;
		static std::normal_distribution<> normal;

	public:
		// Initialise the engine with a seed
		static void seed(unsigned long value);

		// Generate from distributions
		static double rand();
		static double randn();
};

#endif

