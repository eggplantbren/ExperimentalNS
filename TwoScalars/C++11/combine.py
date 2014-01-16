from pylab import *

all_logx = []

for k in xrange(0, 10):
	# Fake sets of choices
	choices = (rand(100) <= rand()).astype('int')

	edge = array([0., 0.])
	logx = empty((len(choices), 2))

	for i in xrange(0, len(choices)):
		logx[i, :] = edge + log(rand(2))
		edge[choices[i]] = logx[i, choices[i]]

	plot(logx[:,0], logx[:,1], 'bo-', alpha=0.25)

	all_logx.append(logx)
	axis('equal')
show()

all_logx = vstack(all_logx)
print(argsort(all_logx[:,0]))
print(argsort(all_logx[:,1]))

