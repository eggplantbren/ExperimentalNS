# Display file for Gravity
from pylab import *

output = atleast_2d(loadtxt('Output/output0.txt'))

figure(figsize=(13, 6))
ion()
hold(False)
for i in xrange(0, output.shape[0]):
	model = output[i, 0:-1]
	x, y = model[0:1000], model[1000:2000]
	vx, vy = model[3000:4000], model[4000:5000]
	subplot(1,2,1)
	plot(x, y, 'k.')
	axis([-10, 10, -10, 10])
	subplot(1,2,2)
	plot(vx, vy, 'k.')
	axis([-10, 10, -10, 10])
	title(i+1)
	draw()

ioff()
show()

