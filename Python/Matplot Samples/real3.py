import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 10, 1000)
f=100
y =np.sin(x)

# You probably won't need this if you're embedding things in a tkinter plot...
plt.ion()

fig = plt.figure()
line1, = plt.plot(x, y, 'r-') # Returns a tuple of line objects, thus the comma

for phase in np.linspace(0, 10*np.pi, 500):
    line1.set_ydata(np.sin(x+phase))
    fig.canvas.draw()
