import serial
import time
ser=serial.Serial(port='\\.\COM14', baudrate=9600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)
#ser.open()
ser.isOpen()
adc=''
time.sleep(5)
while(1):
	if(ser.inWaiting()>0):
		c=ser.read(1)
		if(c=='r'):
			adc=ser.read(4)
		elif(c=='b'):
			print 'begin'
		elif(c=='e'):
			print 'end'
	if(adc != ''):		
		d=int(adc)
		print d
		adc=''
