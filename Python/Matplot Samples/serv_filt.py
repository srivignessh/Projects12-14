import sys, serial
import numpy as np
import socket
from time import sleep
import time
from collections import deque
from matplotlib import pyplot as plt
import random
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
      self.addToBuf(self.x, data)
    
# plot class
class AnalogPlot:
  # constr
  def __init__(self, analogData):
    # se plot to animated
    plt.ion() 
    self.axline, = plt.plot(analogData.x)
    plt.ylim([-2, 2])
 
  # update plot
  def update(self, analogData):
    self.axline.set_ydata(analogData.x)
    plt.draw()
 
# main() function
def main():
  HOST = 'localhost'   # Symbolic name meaning the local host
  PORT = 114    # Arbitrary non-privileged port
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  print 'Socket created'
  try:
    s.bind((HOST, PORT))
  except socket.error , msg:
    print 'Bind failed. Error code: ' + str(msg[0]) + 'Error message: ' + msg[1]
    sys.exit()
  print 'Socket bind complete'
  s.listen(1)
  print 'Socket now listening'
  # Accept the connection once (for starter)
  (conn, addr) = s.accept()
  print 'Connected with ' + addr[0] + ':' + str(addr[1])
  stored_data = ''
  data=[]
  fs = 5000.0
  lowcut = 0.0
  highcut = 50.0
  analogData = AnalogData(100)
  analogPlot = AnalogPlot(analogData)
  analogDataF = AnalogData(100)
  analogPlotF = AnalogPlot(analogDataF)
  pBuf=[];
  print 'plotting data...'
  while True:
    try:
       datai = conn.recv(1024)
       data.append(float(datai))
       pBuf.append(float(datai))
       reply='OK'
       # SEND REPLY
       conn.send(reply)
    except:
        pass
    try:
      analogData.add(data)
      data=[]
      analogPlot.update(analogData)
    except:
       pass  
    if(len(pBuf)>=250):
        y = butter_bandpass_filter(pBuf, lowcut, highcut, fs, order=6)
        analogDataF.add(1)
        analogPlotF.update(analogDataF)
        pBuf.pop(0)    
    #except:
     #   print 'Unable to plot filtersignal'
        
# call main
if __name__ == '__main__':
  main()
