#include <iostream>
#include <iomanip>
#include "RNG.h"
#include "Walker.h"
#include "Models/Example.h"

using namespace std;

int main()
{
	RNG::seed();

	Walker<Example> walker;
	walker.initialise();

	for(int i=0; i<1000; i++)
		walker.advance(1000);

	cout<<walker.get_point()<<endl;

	return 0;
}

