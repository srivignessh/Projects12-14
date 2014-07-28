import numpy as np
L1=5;L2=5;L=7
for u in np.linspace(0,np.pi/2,180):
            for v in np.linspace(np.pi/2,np.pi,180):
                f=L1*np.sin(u)+L2*np.sin(v)
                if(abs(f-L)<=0.001):
                     print 180*u/np.pi,v*180/np.pi
                     print L1*np.cos(u)+L2*np.cos(v)
