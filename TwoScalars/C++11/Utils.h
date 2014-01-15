#ifndef _Utils_
#define _Utils_

#include <vector>

double mod(double y, double x);
int mod(int y, int x);
double logsumexp(double* logv, int n);
double logsumexp(const std::vector<double>& logv);
double logsumexp(double a, double b);

#endif

