import sys, serial
import numpy as np
from time import sleep
import time
from collections import deque
from matplotlib import pyplot as plt
import random
# class that holds analog data for N samples
class AnalogData:
  # constr
  def __init__(self, maxLen):
    self.x = deque([0.0]*maxLen)
    self.maxLen = maxLen
 
  # ring buffer
  def addToBuf(self, buf, val):
    if len(buf) < self.maxLen:
      buf.append(val)
    else:
      buf.pop()
      buf.appendleft(val)
 
  # add data
  def add(self, data):
    j=0
    while(j<10):
      self.addToBuf(self.x, data[j])
      j=j+1
    
# plot class
class AnalogPlot:
  # constr
  def __init__(self, analogData):
    # se plot to animated
    plt.ion() 
    self.axline, = plt.plot(analogData.x)
    plt.ylim([0, 5])
 
  # update plot
  def update(self, analogData):
    self.axline.set_ydata(analogData.x)
    plt.draw()
 
# main() function
def main():
  data=[]
  ser=serial.Serial('COM3',9600)
  analogData = AnalogData(100)
  analogPlot = AnalogPlot(analogData)
  print 'plotting data...'
  while True:
    i=0
    try:
        while(i<10):
            s=ser.readline()
            #print s
            r=int(s)
            r=r*3.61/1024;
            data.append(r)
            i=i+1;
    except:
        pass  
    try:
      analogData.add(data)
      data=[]
      analogPlot.update(analogData)
    except:
       pass
        
  # close serial
  ser.flush()
  ser.close()
 
# call main
if __name__ == '__main__':
  main()
