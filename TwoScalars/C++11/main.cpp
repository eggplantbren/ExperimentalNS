#include <iostream>
#include <iomanip>
#include <fstream>
#include "RNG.h"
#include "Walker.h"
#include "Models/Potts.h"

using namespace std;

int main()
{
	launch_walker<Potts>(0, 2000, 10000, 10);
	return 0;
}

