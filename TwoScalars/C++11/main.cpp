#include <iostream>
#include <iomanip>
#include "RNG.h"

using namespace std;

int main()
{
	RNG::seed(0);

	cout<<setprecision(12);
	for(int i=0; i<1000000; i++)
		cout<<RNG::randInt(5)<<endl;

	return 0;
}

