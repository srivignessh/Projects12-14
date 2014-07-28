import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate
import matplotlib.animation as animation
from time import time
dt = 1.0/30 # 30 fps
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
        dp=t;p=0;q=0;dq=0;
        #e=np.linspace(0,5,10)
        #l=e[int(30*t)]
        L1=5;L2=5;L=5+5*t;Q=2+5*t;f=0;
        for u in np.linspace(0,np.pi,360):
            for v in np.linspace(0,np.pi,360):
                f=L1*np.sin(u)+L2*np.sin(v)
                g=L1*np.cos(u)+L2*np.cos(v)
                if(abs(f-L)<=0.05 and abs(g-Q)<=0.05):
                    x[1]=L1*np.sin(u)
                    x[2]=L1*np.sin(u)+L2*np.sin(v)
                    y[1]=L1*np.cos(u)
                    y[2]=L1*np.cos(u)+L2*np.cos(v)
                    #print x[1],y[1]
                    f=1;
                    break;
            if(f==1):
                break;
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
