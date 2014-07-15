from pylab import *

x = linspace(0., 1., 1001)
p = exp(-100.*(x - 0.5)**2 - 1.*sin(2.*pi*x/0.5))
Z = trapz(p, x=x)
print(Z)
plot(x, p/Z)
show()

