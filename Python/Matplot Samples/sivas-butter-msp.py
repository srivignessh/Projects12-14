import sys, serial
import numpy as np
from collections import deque
from matplotlib import pyplot as plt
import random
import time
from scipy.signal import freqz
from scipy.signal import butter, lfilter
def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 1 * fs
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return b, a


def butter_bandpass_filter(data, lowcut, highcut, fs, order=5):
    b, a = butter_bandpass(lowcut, highcut, fs, order=order)
    y = lfilter(b, a, data)
    return y


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
    plt.ylim([0, 1024])
 
  # update plot
  def update(self, analogData):
    self.axline.set_ydata(analogData.x)
    plt.draw()
 
# main() function
def main():
  fs = 1000.0
  lowcut = 0.0
  highcut = 50.0
  data=[]
  ser=serial.Serial('COM2',9600)
  analogData = AnalogData(200)
  analogPlot = AnalogPlot(analogData)
  analogDataF = AnalogData(200)
  analogPlotF = AnalogPlot(analogDataF)
  pBuf=[];
  print 'plotting data...'
  while True:
    i=0
    data=[]
    try:
        while(i<10):
            s=ser.readline()
            r=int(s)
            data.append(r)
            i=i+1;
            pBuf.append(r)
    except:
        pass
        #print 'Serial reading'
    try:
        analogData.add(data)
        analogPlot.update(analogData)
    except:
       print 'Unable plot original signal'
    try:
      
      if(len(pBuf)>10):
        y = butter_bandpass_filter(pBuf, lowcut, highcut, fs, order=6)
        analogDataF.add(y)
        analogPlotF.update(analogDataF)
        g=0
        while(g<10):
            pBuf.pop(0)
            g=g+1;
            
    except:
        print 'Unable to plot filtersignal'
  # close serial
  ser.flush()
  ser.close()
# call main
if __name__ == '__main__':
  main()
