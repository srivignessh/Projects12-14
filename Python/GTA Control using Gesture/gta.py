import win32api
import time,math
import serial
import time
import win32con
ser=serial.Serial(port='\\.\COM2', baudrate=9600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)
#ser.open()
ser.isOpen()
adc=''
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
                if(d>650):
                        print "1"
                        win32api.keybd_event(0x57, 0, 0, 0)
                        win32api.keybd_event(0x41, 0, 0, 0)
                        time.sleep(.3)
                        win32api.keybd_event(0x41,0 ,win32con.KEYEVENTF_KEYUP ,0)
                        win32api.keybd_event(0x57,0 ,win32con.KEYEVENTF_KEYUP ,0)
                elif(d<550):
                        print "2"
                        win32api.keybd_event(0x57, 0, 0, 0)
                        win32api.keybd_event(0x44, 0, 0, 0)
                        time.sleep(.3)
                        win32api.keybd_event(0x44,0 ,win32con.KEYEVENTF_KEYUP ,0)
                        win32api.keybd_event(0x57,0 ,win32con.KEYEVENTF_KEYUP ,0)
                else:
                        print "3"
                        win32api.keybd_event(0x57, 0, 0, 0)
                        time.sleep(.3)
                        win32api.keybd_event(0x57,0 ,win32con.KEYEVENTF_KEYUP ,0)
