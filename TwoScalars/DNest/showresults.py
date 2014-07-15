from pylab import *
import postprocess

# Load the levels from the DNest run
levels = loadtxt('levels.txt')
sample_info = loadtxt('sample_info.txt')

# Get logx of samples from the DNest run
result = postprocess.postprocess()

# Relationship between logl and logx based on the DNest run
logx = hstack([levels[:,0], result[2].flatten()])
logl = vstack([levels[:,1:3], sample_info[:,1:3]])

print(logl)

