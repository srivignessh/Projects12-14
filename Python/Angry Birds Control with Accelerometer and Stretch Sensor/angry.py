import serial														#importing module for serial communiation
import time,math													#importing module for mathematical operation and time operations 
import win32api,win32con,win32com.client							#importing module for windows device control
def click(x,y): 													# Function to click the screen at (x,y)
	win32api.SetCursorPos((x,y)) 									#move the mouse to (x,y)
	win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,x,y,0,0) 	#press the mouse at (x,y)
	win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,x,y,0,0) 		#release the mouse at (x,y)
def click_and_drag(x,y):											#Function to click and drag the screen at (x,y)
	win32api.SetCursorPos((x,y))									#move the mouse to (x,y)
	win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,x,y,0,0) 	#press the mouse at (x,y)
def main():															#main function
	win32api.Sleep(100)												#Wait for 100 ms
	ser=serial.Serial(port='\\.\COM2', baudrate=9600, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=1)#Serial object
	ser.isOpen()													#Wait for serial port opening with the configuration above 
	accr='';strh=''; 												#Initialize String for Storing Accelerometer and Stretch Sensor Reading
	time.sleep(5)													#now open the angry game within 5 sec or more
	while(1):														#Game loop 		
		if(ser.inWaiting()>0):										#Wait for serial port to refresh and next read to takes place
			c=ser.read(1)											#Read a single char from buffer
			if(c=='b'):												#If the character is 'b' then get ready begin 
				print 'begin'										#print begin in commmand window
				click_and_drag(375,400)								#click and drag the bird at (375,400) pixel of the screen 
				click_and_drag(375,400)
				click_and_drag(375,400)
			elif(c=='a'):											#If the character is 'a' then next four characters represent reading of accelerometer
				accr=ser.read(4)									#Store the four byte reading of accelerometer 
			elif (c=='s'):											#If the character is 'a' then next four characters represent reading of strech sensor
				strh=ser.read(4)									#Store the four byte reading of strech sensor
			elif(c=='e'):											#If the character is 'e' then get ready to release the bird
				print 'end'											#print end in commmand window
				click(x,y)											#Release the bird now at (x,y)
		if(accr != '' and strh != ''):								#if both values succesfully read then go inside
			a=int(accr);s=int(strh);                                        #Convert the four byte characters to integers		
                        ma=min(ma,a);ms=min(mb,b)
                        Ma=max(Ma,a);Ms=max(Mb,b)
			theta=(m-Ma)       			#Using y=mx+c to get theta from accelerometer reading
			r=(m-Ms)											#Using y=mx+c to get radius from sterch sensor reading
			x = int(371+r*math.sin(theta))							#Using x=a+b*cos(theta) parametric cooridates of circle
			y = int(411+r*math.cos(theta))							#Using x=a+b*cos(theta) parametric cooridates of circle
			click_and_drag(x,y)										#Click and drag for every new reading 
			print r,theta											#Print the reading for r and theta
			accr='';strh=''											#Reset the readings of strech sensor and accelerometer
if __name__=='__main__':
	main()															#Call the main funtion
