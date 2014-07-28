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
    self.ax = deque([0.0]*maxLen)
    self.ay = deque([0.0]*maxLen)
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
    assert(len(data) == 2)
    self.addToBuf(self.ax, data[0])
    self.addToBuf(self.ay, data[1])
    
# plot class
class AnalogPlot:
  # constr
  def __init__(self, analogData):
    # se plot to animated
    plt.ion() 
    self.axline, = plt.plot(analogData.ax)
    self.ayline, = plt.plot(analogData.ay)
    plt.ylim([0, 1024])
 
  # update plot
  def update(self, analogData):
    self.axline.set_ydata(analogData.ax)
    self.ayline.set_ydata(analogData.ay)
    plt.draw()
 
# main() function
def main():
  # expects 1 arg - serial port string
  #if(len(sys.argv) != 2):
  #  print 'Example usage: python showdata.py "/dev/tty.usbmodem411"'
  #  exit(1)
 
 #strPort = '/dev/tty.usbserial-A7006Yqh'
 # strPort = sys.argv[1];
 
  # plot parameters
  analogData = AnalogData(100)
  analogPlot = AnalogPlot(analogData)
  #data = []
  r1=''
  r2=''
  print 'plotting data...'
 
  # open serial port
  #ser = serial.Serial("COM2", 9600)
  #serialPort = "COM30"
  #baudRate = 115200
  #ser = serial.Serial(serialPort , baudRate, timeout=0, writeTimeout=0) #ensure non-blocking
  ser=serial.Serial(port='\\.\COM3', baudrate=9600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)
  ser.isOpen()
  accr=''
  strh=''
  data=[500,500]
  x=0;y=0;cd=0;su=0;t=0
  while True:
    try:
        s=ser.readline()
        r=int(s)
        data=[r,r]
    except:
        pass
    if(len(data) == 2):
        analogData.add(data)
        analogPlot.update(analogData)
        
  # close serial
  ser.flush()
  ser.close()
 
# call main
if __name__ == '__main__':
  main()
