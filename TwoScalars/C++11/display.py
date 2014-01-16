# Display file for Potts
from pylab import *

output = atleast_2d(loadtxt('output.txt'))

ion()
hold(False)
for i in xrange(0, output.shape[0]):
	x = output[i, 0:-1].reshape((32, 32))
	imshow(x, interpolation='nearest')
	title(i+1)
	draw()

ioff()
show()

