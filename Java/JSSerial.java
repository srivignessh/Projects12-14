import java.applet.*;
import netscape.javascript.*;

/*
available()
read()
readChar()
readBytes()
readBytesUntil()
readString()
readStringUntil() 
buffer()
bufferUntil()
last()
lastChar() 
write()
clear()
stop()
list()

javac -classpath .:/System/Library/Frameworks/JavaVM.framework/Versions/1.6.0/Home/lib/plugin.jar JavaScriptArduino.java
*/

public class JSSerial extends Applet
{
	JSObject window;
	SerialThread thread;
	Serial serial;

	// Serial Variables
	String[] portList;
	String sPortList = "";
	StringBuffer readBuffer = new StringBuffer();
	StringBuffer writeBuffer = new StringBuffer();	

	Boolean startSerial = false;
	Boolean listPorts = true;
	Boolean stopSerial = false;
	Boolean serialRunning = false;
	
	// Serial Init Vars
	String name;
	int irate;
	char iparity;
	int idatabits;
	float istopbits;


	public void init()
	{
		System.out.println("Starting JavaScript Serial Applet");				
	}
	
	public void start()
	{
		//window = JSObject.getWindow(this);

		if (window != null)
		{
			System.out.println("Have reference to JavaScript DOM");
			//String[] args = {"Yay! Java to JavaScript Communication is workign"};		
			//window.call("fromJava",args);
		}
		else
		{
			//System.out.println("Sorry, this browser isn't working correctly");
		}
		
		thread = new SerialThread();
		thread.start();
		
		//portList = Serial.list();
	}
		
	/*
	public void startSerial()
	{
		serial = new Serial(this);
	}
	*/
	
	public void startSerial(String name)
	{
		this.name = name;
		this.startSerial = true;
	}

	/*
	public void startSerial(String name, int irate)
	{
		serial = new Serial(this, name, irate);
	}
	
	public void startSerial(String name, int irate,
                 char iparity, int idatabits, float istopbits)
    {
		serial = new Serial(this, name, irate, iparity, idatabits, istopbits);
    }
	*/
	
	//public void serialEvent(Serial s)
	//{
		//String[] args = {s.readString()};
		//System.out.println(args[0]);
		//window.call("serialEvent",args);
	//}

	public int read()
	{
		return serial.read();
	}
	
	public int readByte()
	{
		return serial.read();
	}

	public byte[] readBytesUntil(int interesting) 
	{
		return serial.readBytesUntil(interesting);
	}

  	public byte[] readBytes() 
  	{
		return serial.readBytes();
	}

	public char readChar() 
	{
		return serial.readChar();
	}
	
	public String readString()
	{
		return serial.readString();
		
		/*String returnString = readBuffer.toString();
		readBuffer = new StringBuffer();
		return returnString;*/
		
		//readBuffer = readBuffer.delete(0,readBuffer.length()-1);
		//readBuffer.setLength(0);
		
		
	}
	
	public String readStringUntil(int interesting)
	{
		return serial.readStringUntil(interesting);
	}

	
	public void stop()
	{
		stopSerial = true;
	}
			
	public int available()
	{
		//return readBuffer.length();
		return serial.available();
	}

	/*
		document.JSSerial.writeInt(integer)
		document.JSSerial.writeByte(byte)
		document.JSSerial.writeString(string)
		document.JSSerial.writeBytes(byte[])	
	*/
	
	public void writeInt(int intToWrite)
	{
		System.out.println("Write int: " + intToWrite);
		String aChar = new Character((char)intToWrite).toString();
		writeBuffer.append(aChar);
	}
	
	public void writeByte(byte byteToWrite)
	{
		System.out.println("Write byte: " + byteToWrite);
		String aChar = new Character((char)byteToWrite).toString();
		writeBuffer.append(aChar);
	}
	
	public void writeBytes(byte[] bytesToWrite)
	{
		System.out.println("Write bytes: " + bytesToWrite);
		for (int i = 0; i < bytesToWrite.length; i++)
		{
			String aChar = new Character((char)bytesToWrite[i]).toString();
			writeBuffer.append(aChar);
		}
	}
	
	public void writeString(String stringToWrite)
	{
		System.out.println("Write String: " + stringToWrite);
		writeBuffer.append(stringToWrite);
	}
	
	public int last()
	{
		return serial.last();
	}
	
	public char lastChar()
	{
	  	return serial.lastChar();
	}
	
	public void clear()
	{
		serial.clear();
		//readBuffer.delete(0,readBuffer.length());
	}
	
	public String listPorts()
	{
		for (int i = 0; i < portList.length; i++)
		{
			System.out.println(portList[i]);
			sPortList += portList[i];
			if (i < portList.length - 1)
			{
				sPortList += ",";
			}
		}
		return sPortList;
	}
	
	/*public void serialEvent(Object seriallib)
	{
		System.out.println("Serial Event");
		//window.call("serialEvent",new Object[0]);
	}*/
		
	class SerialThread extends Thread 
	{
		//Serial serial;

    	public void run() 
    	{
    		while (true)
    		{
    			//System.out.println("Thread Running");
    			
				if (listPorts)
				{
					portList = Serial.list();
					listPorts = false;
				}
				else if (startSerial)
    			{
	    			startSerial = false;
	    			serial = new Serial(JSSerial.this, name);
	    			
	    			serialRunning = true;
    			} 
    			else if (stopSerial)
    			{
    				stopSerial = false;
					serial.stop();
					serialRunning = false;
    			} 
    			else if (serialRunning)
    			{
    				/*String read = serial.readString();
    				
    				if (read != null)
    				{
    					//System.out.println(read);
    					readBuffer.append(read);
    				}*/
    				
    				// This needs more work
    				while (writeBuffer.length() > 0)
    				{
    					serial.write(writeBuffer.charAt(0));
    					System.out.println("Writing: " + writeBuffer.charAt(0));
    					writeBuffer = writeBuffer.deleteCharAt(0);
    				}
    			}
    			
    		
	            try {
					sleep(10);
	    		} catch (InterruptedException e) {}
	    	}
		}
    }
}