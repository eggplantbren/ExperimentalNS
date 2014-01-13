from Walker import *
import matplotlib.pyplot as plt

def do_run(filename):
	walker = Walker()
	walker.initialise()
	print(walker.direction)

	plt.ion()
	plt.hold(False)
	for i in xrange(0, 100):
		success = walker.advance()

		walker.point.plot_state(i, walker.direction)
		plt.draw()

		if success is False:
			break

	import cPickle as pickle
	pickle.dump(walker, open(filename, 'wb'))

if __name__ == '__main__':
	for i in xrange(0, 10):
		do_run('walker' + str(i+1) + '.dat')

