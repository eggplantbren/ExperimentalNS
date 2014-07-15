from pylab import *
import postprocess
from postprocess import logsumexp

# Load the levels from the DNest run
levels = loadtxt('levels.txt')
sample_info = loadtxt('sample_info.txt')

# Get logx of samples from the DNest run
result = postprocess.postprocess()

# Relationship between logl and logx based on the DNest run
logx = hstack([levels[:,0], result[2].flatten()])
logl = vstack([levels[:,1:3], sample_info[:,1:3]])
order = argsort(logx)[::-1]
logx = logx[order]
logl = logl[order, :]

# Now treat logx, logl as "levels" and use them as scaffolding to locate
# the points from the directional runs
levels = empty((logx.size, levels.shape[1]))
levels[:, 0] = logx
levels[:, 1:3] = logl
scalars = loadtxt('scalars.txt')
sample = loadtxt('output.txt')
sample_info = empty((scalars.shape[0], sample_info.shape[1]))
sample_info[:,1:3] = scalars[:, 0:2]

# log prior weights
result = postprocess.postprocess(loaded=[levels, sample_info, sample],\
					temperature=1E300, plot=False)
logx = result[2]
if logx.min() < levels[:,0].min():
	print('# WARNING: Went beyond innermost scaffolding point.')
logw = result[-1].flatten()
savetxt('logw.txt', logw)

# Estimate normalising constant of canonical distribution in truth.py
temp = logw + 10.*scalars[:,0] + 1.*scalars[:,2]
logz = logsumexp(temp) - log(len(temp))
print(logz)
plot(exp(temp - temp.max()))
show()

