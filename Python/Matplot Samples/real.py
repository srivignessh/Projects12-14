import time
import numpy as np
import matplotlib.pyplot as plt
fig=plt.figure()
plt.axis([0,1000,0,1])
i=0
x=list()
y=list()

plt.ion()
plt.show()

while i <1000:
    temp_y=0.5
    x.append(40)
    y.append(temp_y)
    plt.scatter(i,np.sin(i))
    i+=40
    plt.draw()
