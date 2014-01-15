#include <iostream>
#include <iomanip>
#include "RNG.h"
#include "Walker.h"
#include "Models/Example.h"

using namespace std;

int main()
{
	RNG::seed(0);

	Walker<Example> walker;
	walker.initialise();

	return 0;
}

