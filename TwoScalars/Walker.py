import numpy as np
import numpy.random as rng
import copy
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
		self.direction = -np.log(rng.rand(self.num_scalars))
		self.direction /= self.direction.sum()

		# Give a hard edge to the distribution
		self.edge = -np.Inf*np.ones(self.num_scalars)

		# Keep track of which choices were made
		self.choices = []

	def advance(self, steps=10000):
		choice = rng.choice(np.arange(0, self.num_scalars),\
				p=self.direction)
		self.choices.append(choice)
		self.edge[choice] = self.point.scalars[choice]

		accept = 0
		for i in xrange(0, steps):
			proposal = copy.deepcopy(self.point)
			logH = proposal.perturb()
			if logH > 0.:
				logH = 0.
			if np.all(proposal.scalars >= self.edge) \
				and rng.rand() <= np.exp(logH):
				self.point = proposal
				accept += 1
		print('Accepted {a}/{b}'.format(a=accept, b=steps))

		if accept <= 0.05*steps:
			return False
		return True


if __name__ == '__main__':
	import matplotlib.pyplot as plt

	walker = Walker()
	walker.initialise()
	print(walker.direction)

	plt.ion()
	plt.hold(False)
	for i in xrange(0, 10000):
		plt.hist(walker.point.x, 30)
		plt.title(i)
		plt.draw()
		success = walker.advance()
		if success is False:
			break

	plt.ioff()
	plt.show()

