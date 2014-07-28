import pylab
from pylab import *
fig = pylab.figure(1)
ax = fig.add_subplot(111)
ax.grid(True)
ax.set_title("Realtime Waveform Plot")
ax.set_xlabel("Time")
ax.set_ylabel("Amplitude")
ax.axis([0,100,-1.5,1.5])
line1=ax.plot([],[],'')

manager = pylab.get_current_fig_manager()
values=[]
values = [x for x in range(100)]
Ta=0.01
fa=1.0/Ta
fcos=3.5
K=cos(2*pi*fcos*Ta)

T0=1.0
T1=K
def SinwaveformGenerator(arg):
  global values,T1,K,T0,accr,strh
  Tnext=((K*T1)*2)-T0
  values.append(Tnext)
  T0=T1
  T1=Tnext

def RealtimePloter(arg):
  global values
  CurrentXAxis=pylab.arange(len(values)-100,len(values),1)
  line1[0].set_data(CurrentXAxis,pylab.array(values[-100:]))
  ax.axis([CurrentXAxis.min(),CurrentXAxis.max(),-1.5,1.5])
  manager.canvas.draw()
  manager.show()

timer = fig.canvas.new_timer(interval=1)
timer.add_callback(RealtimePloter, ())
timer2 = fig.canvas.new_timer(interval=1)
timer2.add_callback(SinwaveformGenerator, ())
timer.start()
timer2.start()
pylab.show()
