import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(0, 0.1, 50000)
x=0;y=0
plt.grid()
f=10000
#for k in range(-100,100):
#    x+=2*np.sinc(k/2)*pow(np.e,1j*t*k*np.pi/2)
x=np.sin(2*np.pi*f*t)
plt.plot(t,x, 'k')
plt.show()
