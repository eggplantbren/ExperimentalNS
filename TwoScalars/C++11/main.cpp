#include <iostream>
#include <iomanip>
#include "RNG.h"

using namespace std;

int main()
{
	RNG::seed(0);

	cout<<setprecision(12);
	for(int i=0; i<20; i++)
		cout<<RNG::rand()<<endl;

	return 0;
}

