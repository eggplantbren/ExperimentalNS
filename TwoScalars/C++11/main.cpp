#include <iostream>
#include <iomanip>
#include <fstream>
#include "RNG.h"
#include "Walker.h"
#include "Models/Potts.h"

using namespace std;

int main()
{
	RNG::seed();

	Walker<Potts> walker;
	walker.initialise();

	fstream fout("output.txt", ios::out);
	for(int i=0; i<2000; i++)
	{
		walker.advance(100000);
		if(i%10 == 0)
			fout<<setprecision(3)<<walker.get_point()<<endl;
	}
	fout.close();

	return 0;
}

