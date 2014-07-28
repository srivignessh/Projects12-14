import sys, serial
import numpy as np
from collections import deque
from matplotlib import pyplot as plt
import random
from scipy.signal import freqz
from scipy.signal import butter, lfilter
def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 0.5 * fs
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
    while(j<30):
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
  lowcut = 100.0
  highcut = 500.0
  data=[]
  ser=serial.Serial('COM3',9600)
  analogData = AnalogData(100)
  analogPlot = AnalogPlot(analogData)
  analogDataF = AnalogData(100)
  analogPlotF = AnalogPlot(analogDataF)
  pBuf=[];
  print 'plotting data...'
  while True:
    i=0
    data=[]
    try:
        while(i<30):
            s=ser.readline()
            #print s
            r=int(s)
            data.append(r)
            i=i+1;
    except:
        pass  
    try:
      analogData.add(data)
      analogPlot.update(analogData)
    except:
       pass
    try:
      y = butter_bandpass_filter(data, lowcut, highcut, fs, order=6)
      analogDataF.add(y)
      analogPlotF.update(analogDataF)
    except:
      pass
  # close serial
  ser.flush()
  ser.close()
 
# call main
if __name__ == '__main__':
  main()
