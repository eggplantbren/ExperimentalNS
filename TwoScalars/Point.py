import numpy as np
import numpy.random as rng

class Point:
	"""
	Represents a point in parameter space.
	"""
	def __init__(self, num_params=10000):
		self.num_params = num_params
		self.x = np.empty(self.num_params)

	def from_prior(self):
		"""
		Initialise the point using the prior.
		"""
		self.x = rng.rand(self.num_params)
		self.calculate_scalars()

	def perturb(self):
		"""
		Does a metropolis-hastings proposal that respects the prior (DNest
		style).
		"""
		which = rng.randint(self.num_params)
		self.x[which] += 10.**(1.5 - 6.*rng.rand())*rng.randn()
		self.x[which] = np.mod(self.x[which], 1.)
		self.calculate_scalars()
		return 0.

	def calculate_scalars(self):
		"""
		Evaluate all the relevant scalars.
		"""
		self.scalars = [np.sum(self.x > 0.5),\
					-0.5*np.sum(self.x**2)]

