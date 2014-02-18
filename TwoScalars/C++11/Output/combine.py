from pylab import *

def rank(x):
	y = sort(x)
	r = zeros(len(x)).astype('int64')
	for i in xrange(0, len(x)):
		index = nonzero(y == x[i])[0]
		assert len(index) == 1
		r[i] = index
	return r

all_logx = []

for k in xrange(0, 10000):
	# Load choices
	try:
		choices = loadtxt('choices' + str(k) + '.txt')
	except:
		break

	edge = array([0., 0.])
	logx = empty((len(choices), 2))

	for i in xrange(0, len(choices)):
		logx[i, :] = edge + log(rand(2))
		edge[choices[i]] = logx[i, choices[i]]

	plot(logx[:,0], logx[:,1], '-')

	all_logx.append(logx)
	axis('equal')
show()

all_logx = vstack(all_logx)
print(all_logx)

