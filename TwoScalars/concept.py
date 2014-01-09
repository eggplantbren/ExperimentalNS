import numpy as np
import numpy.random as rng
import matplotlib.pyplot as plt

def ns_run(steps=100, direction=0.5):
	keep = np.empty((steps, 2))

	# Initial boundary
	logx_max, logy_max = 0., 0.

	# Initial position
	logx = logx_max + np.log(rng.rand())
	logy = logy_max + np.log(rng.rand())

	keep[0, :] = np.array([logx, logy])
	for i in xrange(0, steps-1):
		# Generate next boundary
		if rng.rand() <= direction:
			logx_max = logx
		else:
			logy_max = logy

		# Generate next position
		logx = logx_max + np.log(rng.rand())
		logy = logy_max + np.log(rng.rand())
		keep[(i+1), :] = np.array([logx, logy])

	return keep



# MAIN
plt.figure(figsize=(8, 8))

for i in xrange(0, 100):
	keep = ns_run(steps=1000, direction=rng.rand())
	plt.plot(keep[:,0], keep[:,1], '-', alpha=0.1)
plt.xlabel(r'$\log X$', fontsize=20)
plt.ylabel(r'$\log Y$', fontsize=20)
plt.show()

