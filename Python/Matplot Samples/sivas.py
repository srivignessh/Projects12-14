import serial
ser=serial.Serial(port='\\.\COM3', baudrate=9600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)
ser.isOpen()
while True:
    try:
        s=ser.readline(1)
        #print s
        r=int(s)
        print r
    except:
        pass
