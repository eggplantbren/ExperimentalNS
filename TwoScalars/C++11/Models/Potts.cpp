#include "Potts.h"
#include "RNG.h"
#include "Utils.h"

#include <cmath>

using namespace std;

Potts::Potts()
:Point(2)
,x(32, vector<int>(32))
{

}

void Potts::from_prior()
{
	for(size_t i=0; i<x.size(); i++)
		for(size_t j=0; j<x[i].size(); j++)
			x[i][j] = RNG::randInt(num_colors);

	compute_score();
	compute_scalars();
}

void Potts::compute_score()
{
	score = 0;
	score2 = 0;

	// Coordinates of neighbouring cells
	vector<int> ii(4); vector<int> jj(4);

	for(size_t i=0; i<x.size(); i++)
	{
		for(size_t j=0; j<x[i].size(); j++)
		{
			for(int k=0; k<4; k++)
			{
				ii[k] = i;
				jj[k] = j;
			}
			// Down, up, right, left
			ii[0] = mod(i + 1, static_cast<int>(x.size()));
			ii[1] = mod(i - 1, static_cast<int>(x.size()));
			jj[2] = mod(j + 1, static_cast<int>(x[i].size()));
			jj[3] = mod(j - 1, static_cast<int>(x[i].size()));

			for(int k=0; k<4; k++)
				if(x[i][j] == x[ii[k]][jj[k]])
					score++;
			score2 += ((int)i - (int)j)*x[i][j];
		}
	}
}

#include <iostream>

double Potts::perturb()
{
	int reps = 1;
	if(RNG::rand() <= 0.5)
		reps += 1 + RNG::randInt(9);

	// Which cell is being perturbed
	int i, j;

	// Coordinates of neighbouring cells
	vector<int> ii(4); vector<int> jj(4);
	for(int z=0; z<reps; z++)
	{
		i = RNG::randInt(x.size());
		j = RNG::randInt(x[0].size());

		for(int k=0; k<4; k++)
		{
			ii[k] = i;
			jj[k] = j;
		}
		// Down, up, right, left
		ii[0] = mod(i + 1, static_cast<int>(x.size()));
		ii[1] = mod(i - 1, static_cast<int>(x.size()));
		jj[2] = mod(j + 1, static_cast<int>(x[i].size()));
		jj[3] = mod(j - 1, static_cast<int>(x[i].size()));

		// Calculate negative part of delta score
		for(int k=0; k<4; k++)
			if(x[i][j] == x[ii[k]][jj[k]])
				score--;
		score2 -= ((int)i - (int)j)*x[i][j];

		// Perturb the cell
		x[i][j] = RNG::randInt(num_colors);

		// Calculate positive part of delta score
		for(int k=0; k<4; k++)
			if(x[i][j] == x[ii[k]][jj[k]])
				score++;
		score2 += ((int)i - (int)j)*x[i][j];
	}

	compute_scalars();
	return 0.;
}

void Potts::compute_scalars()
{
	scalars[0] = 0.5*score;
	scalars[1] = 0.5*score2;
}

ostream& operator << (ostream& out, const Potts& e)
{
	for(size_t i=0; i<e.x.size(); i++)
		for(size_t j=0; j<e.x[i].size(); j++)
			out<<e.x[i][j]<<' ';
	out<<e.score<<' '<<e.score2;
	return out;
}

