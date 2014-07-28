import numpy as np
L1=5;L2=5;L=7;Q=0;f=0;
x=[0,0];y=[0,0]
for u in np.linspace(0,np.pi/2,180):
            for v in np.linspace(np.pi/2,np.pi,180):
                f=L1*np.sin(u)+L2*np.sin(v)
                g=L1*np.cos(u)+L2*np.cos(v)
                if(abs(f-L)<=0.05 and abs(g-Q)<=0.05):
                    x[0]=L1*np.sin(u)
                    x[1]=L1*np.sin(u)+L2*np.sin(v)
                    y[0]=L1*np.cos(u)
                    y[1]=L1*np.cos(u)+L2*np.cos(v)
                    print x[1],y[1]
                    f=1;
                    break;
            if(f==1):
                break;
            
