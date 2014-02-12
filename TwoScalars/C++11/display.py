# Display file for Potts
from pylab import *

for k in xrange(0, 1000):
	output = atleast_2d(loadtxt('Output/output' + str(k) + '.txt'))

	ion()
	hold(False)
	for i in xrange(0, output.shape[0]):
		x = output[i, 0:-2].reshape((32, 32))
		imshow(x, interpolation='nearest')
		title('Walker ' + str(k) + ', iteration ' + str(i+1))
		draw()

ioff()
show()

