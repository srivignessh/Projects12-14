from numpy import sin, cos
import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate
import matplotlib.animation as animation
from time import time
dt = 1./30 # 30 fps
class Arm():
    def __init__(self):
        [x0,x1,x2]=[0,5,10]
        [y0,y1,y2]=[0,5,10]
        L1=5;L2=5;
        self.origin=[x0,y0]
        self.params = (L1, L2)
        self.t = 0
        self.statex = [x0,x1,x2]
        self.statey = [y0,y1,y2]
    def position(self):
        (L1,L2)=self.params
        x=self.statex
        y=self.statey
        t=self.t
        x[1]=L1*sin(t)
        y[1]=L1*cos(t)
        x[2]=x[1]+L2*cos(t)
        y[2]=y[1]+L2*sin(t)
        #print x,y
        return x,y
    def step(self,dt):
         self.t+=dt
         #print self.t
arm=Arm()
fig = plt.figure()
ax = fig.add_subplot(111, aspect='equal', autoscale_on=False,xlim=(-10, 10), ylim=(-10, 10))
ax.grid()
line, = ax.plot([], [], 'o-', lw=2)
def init():
    line.set_data([], [])
    return line,
def animate(i):
    global arm,dt
    arm.step(dt)
    line.set_data(arm.position())
    return line,
t0 = time()
animate(0)
t1 = time()
interval = 1000 * dt - (t1 - t0)
ani = animation.FuncAnimation(fig, animate, frames=300,interval=interval, blit=True, init_func=init)
plt.show()
