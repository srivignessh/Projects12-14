import pylab
import serial
from pylab import *
import random
fig = pylab.figure(1)
ax = fig.add_subplot(111)
ax.grid(True)
ax.set_title("Realtime Waveform Plot")
ax.set_xlabel("Time")
ax.set_ylabel("Amplitude")
ax.axis([0,100,400,600])
line1=ax.plot([],[],'')
ser=serial.Serial(port='\\.\COM2', baudrate=9600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)
ser.isOpen()
manager = pylab.get_current_fig_manager()
values=[]
values = [x for x in range(100)]
accr=''
strh=''
a=500
def SinwaveformGenerator(arg):
  global values,accr,strh,a
  if(ser.inWaiting()>0):
        c=ser.read(1)
        if(c=='b'):
            print 'begin'
        elif(c=='s'):            
            for i in range(4):
                   u=ser.read()
                   accr+=ser.read()
        elif (c=='a'):
            for i in range(4):
                   u=ser.read()
                   strh+=ser.read()
        elif(c=='e'):
            print 'end'
  if(accr != '' and strh != ''):
                        a=int(accr);s=int(strh)
                        print a,s
                        accr='';strh=''
  values.append(a)
def RealtimePloter(arg):
  global values
  CurrentXAxis=pylab.arange(len(values)-100,len(values),1)
  line1[0].set_data(CurrentXAxis,pylab.array(values[-100:]))
  ax.axis([CurrentXAxis.min(),CurrentXAxis.max(),400,600])
  manager.canvas.draw()
  manager.show()

timer = fig.canvas.new_timer(interval=1)
timer.add_callback(RealtimePloter, ())
timer2 = fig.canvas.new_timer(interval=1)
timer2.add_callback(SinwaveformGenerator, ())
timer.start()
timer2.start()
pylab.show()
