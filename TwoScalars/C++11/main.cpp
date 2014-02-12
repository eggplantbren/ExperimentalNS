#include <iostream>
#include <iomanip>
#include <fstream>
#include "RNG.h"
#include "Walker.h"
#include "Models/Potts.h"

using namespace std;

int main()
{
	RNG::seed(0);

	for(int i=0; i<10; i++)
		launch_walker<Potts>(i, 2000, 10000, 10);
	return 0;
}

