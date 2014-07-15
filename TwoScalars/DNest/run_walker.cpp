#include <iostream>
#include "Start.h"
#include "MyModel.h"
#include "Walker.h"

using namespace std;
using namespace DNest3;

int main(int argc, char** argv)
{
	int junk = system("rm scalars.txt output.txt");
	MTSampler<MyModel> sampler = setup_mt<MyModel>(argc, argv);

	while(true)
		launch_walker<MyModel>(100, 1000, 10);

	return 0;
}

