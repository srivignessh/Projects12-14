from math import *
class Arm():
    def __init__(self):
        [x0,x1,x2]=[0,5,10]
        [y0,y1,y2]=[0,5,10]
        L1=5;L2=5;
        self.origin=[x0,y0]
        self.params = (L1, L2)
        self.t = 0.0
        self.dt=1.0/30
        self.x = [x0,x1,x2]
        self.y = [y0,y1,y2]
    def position(self):
        (L1,L2)=self.params
        f=0
        def s(U):
            return U*U
        self.t+=self.dt
        t=self.t
        X=t
        Y=t
        Z=hypot(X,Y)
        M1=((Z*Z)+(L1*L1)-(L2*L2))/(2*Z*L1)
        M2=((Z*Z)+(L2*L2)-(L1*L1))/(2*Z*L2)
        try:
            A1=acos(M1)
            B1=acos(M2)
        except:
            f=1
            return self.x,self.y,f
        A=asin(Y/Z)-A1
        B=acos(X/Z)+B1
        print A,B
        self.x=[0,L1*sin(A),L1*sin(A)+L2*sin(B)]
        self.y=[0,L1*cos(A),L1*cos(A)+L2*cos(B)]
        return self.x,self.y,f
arm=Arm()
run=True
while run:
    [x,y,f]=arm.position()
    if(f==1):
        run=False
