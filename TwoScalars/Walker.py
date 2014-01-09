import numpy as np
import numpy.random as rng
from Point import Point

class Walker:
	"""
	A walker
	"""
	def __init__(self):
		pass

	def initialise(self):
		self.point = Point()
		self.point.from_prior()
		self.num_scalars = len(self.point.scalars)

		# Assign a direction for the walker to travel in
		self.direction = -np.log(rng.rand())
		self.direction /= self.direction.sum()

		# Give a hard edge to the distribution
		self.edge = -np.Inf*np.ones(self.num_scalars)

	def advance(self, steps=10000):
		pass

if __name__ == '__main__':
	walker = Walker()
	walker.initialise()

	for i in xrange(0, 100):
		walker.advance()

