import serial
ser=serial.Serial(port='\\.\COM3', baudrate=9600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)
ser.isOpen()
a=[]
i=0;
while True:
    try:
        while(i<100):
            s=ser.readline()
            #print s
            r=int(s)
            a.append(r)
            i=i+1;
        print a
        i=0;
    except:
        pass
