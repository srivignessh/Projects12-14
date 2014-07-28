
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from math import *
import Leap, sys,time
dt = 1.0/30 # 30 fps
class LeapListener(Leap.Listener):
    def on_init(self, controller):
        print "Initialized"
    def on_connect(self, controller):
        print "Connected"
    def on_disconnect(self, controller):
        print "Disconnected"
    def on_exit(self, controller):
        print "Exited"
    def on_frame(self,controller):
        self.frame=controller.frame()
class Arm():
    def __init__(self):
        [x0,x1,x2]=[0,5,10]
        [y0,y1,y2]=[0,5,10]
        L1=5;L2=5;
        self.origin=[x0,y0]
        self.params = (L1, L2)
        self.t = 0
        self.x = [x0,x1,x2]
        self.y = [y0,y1,y2]
    def position(self):
        (L1,L2)=self.params
        def s(U):
            return U*U
        t=self.t
        X=self.x
        Y=self.y
        Z=hypot(X,Y)
        try:
            M1=((Z*Z)+(L1*L1)-(L2*L2))/(2*Z*L1)
            M2=((Z*Z)+(L2*L2)-(L1*L1))/(2*Z*L2)
            A1=acos(M1)
            B1=acos(M2)
        except:
            return self.x,self.y
        A=asin(Y/Z)-A1
        B=acos(X/Z)+B1
        if A>0 and A<=pi and abs(B-A)<=90:
            self.x=[0,L1*sin(A),L1*sin(A)+L2*sin(B)]
            self.y=[0,L1*cos(A),L1*cos(A)+L2*cos(B)]
        return self.x,self.y
    def step(self,x,y):
         self.x=x
         self.y=y
         #print self.t
arm=Arm()
leap = LeapListener()
controller = Leap.Controller()
controller.add_listener(leap)
time.sleep(2)
fig = plt.figure()
ax = fig.add_subplot(111, aspect='equal', autoscale_on=False,xlim=(-10, 10), ylim=(-10, 10))
ax.grid()
line, = ax.plot([], [], 'o-', lw=2)
def init():
    line.set_data([], [])
    return line,
def animate(i):
    x=0;y=0
    global arm,dt,leap
    frame=leap.frame
    if not frame.hands.is_empty:
            hand=frame.hands
            fingers = hand[0].fingers
            if not fingers.is_empty:
                    p=fingers[0].tip_position
                    y=4+(2*p.x/100)
                    x=(2*p.y/100)-5
                    print y,x
    arm.step(x,y)
    line.set_data(arm.position())
    return line,
t0 = time.time()
animate(0)
t1 = time.time()
interval = 1000 * dt - (t1 - t0)
ani = animation.FuncAnimation(fig, animate, frames=300,interval=interval, blit=True, init_func=init)
plt.show()
