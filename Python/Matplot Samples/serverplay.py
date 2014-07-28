import socket
import sys
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
      self.addToBuf(self.x, data[j])
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
dataint=[]
analogData = AnalogData(100)
analogPlot = AnalogPlot(analogData)
print 'plotting data...'
while True:
    # RECEIVE DATA
    data = conn.recv(1024)
    print data
    reply='OK'
    # SEND REPLY
    conn.send(reply)
    try:
      analogData.add(dataint)
      print 'f'
      dataint=[]
      analogPlot.update(analogData)
    except:
       pass
conn.close()
