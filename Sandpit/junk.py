from pylab import *

# Experimenting with stuff from
# http://www.researchgate.net/profile/Clement_Walter/publication/269876959_Point_Process-based_Monte_Carlo_Estimation/links/55f05bb908ae0af8ee1d180e.pdf

def generate_sequence(N=100, iterations=100):
	"""
	Generate a sequence of X values according
	to the Nested Sampling procedure with N particles.
	"""
	keep = zeros(iterations)
	logX = log(rand(N))
	keep[0] = logX.max()
	for i in range(1, iterations):
		which = nonzero(logX == keep[i-1])[0]
		logX[which] = keep[i-1] + log(rand(N))
		keep[i] = logX.max()
	return keep

def log_likelihood(logX):
	"""
	An invented log-likelihood function.
	"""
	logL = (-logX)**0.5
	return logL

logX = generate_sequence()
plot(logX, log_likelihood(logX), 'bo-')
show()

