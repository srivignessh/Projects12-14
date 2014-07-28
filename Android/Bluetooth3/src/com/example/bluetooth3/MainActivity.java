package com.example.bluetooth3;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Method;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.UUID;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

@SuppressLint("HandlerLeak")
public class MainActivity extends Activity {
	  Button connect,upload;
	  TextView textView1,textView2;
	  
	  Handler h;
	  private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); 
	  final int RECIEVE_MESSAGE = 1,Request_Enable_BT=1;		// Status  for Handler
	  private BluetoothAdapter btAdapter = null;
	  private BluetoothSocket btSocket = null;
	  private StringBuilder sb = new StringBuilder();
	  private static String address = "20:13:07:12:06:71";
	  private ConnectedThread mConnectedThread;
	  TextView messageText;
	    int serverResponseCode = 0;
	    ProgressDialog dialog = null;
	       
	    String upLoadServerUri = null;
	    
	    /**********  File Path *************/
	    @SuppressLint("SdCardPath")
		final String uploadFilePath = "/sdcard/";
	    final String uploadFileName = "myfile.txt";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		connect=(Button)findViewById(R.id.button1);
		upload=(Button)findViewById(R.id.button2);

		textView1=(TextView)findViewById(R.id.textView1);
		textView2=(TextView)findViewById(R.id.textView2);
			
		btAdapter = BluetoothAdapter.getDefaultAdapter();		// get Bluetooth adapter
	    checkBTState();
	    
	    h=new Handler(){
	    	public void handleMessage(android.os.Message msg) {
	    		switch (msg.what) {
	            case RECIEVE_MESSAGE:													// if receive message
	            	byte[] readBuf = (byte[]) msg.obj;
	            	String strIncom = new String(readBuf, 0, msg.arg1);					// create string from bytes array
	            	sb.append(strIncom);												// append string
	            	int endOfLineIndex = sb.indexOf("\r\n");							// determine the end-of-line
	            	if (endOfLineIndex > 0) { 											// if end-of-line,
	            		String sbprint = sb.substring(0, endOfLineIndex);				// extract string
	                    sb.delete(0, sb.length());										// and clear
	                    // update TextView
	        			textView1.setText("Data from Arduino: " + sbprint); 
	                 }
	            	//Log.d(TAG, "...String:"+ sb.toString() +  "Byte:" + msg.arg1 + "...");
	            	break;
	    	}};
		};
		
		upload.setOnClickListener(new OnClickListener() {            
            @Override
            public void onClick(View v) {
            	
                dialog = ProgressDialog.show(MainActivity.this, "", "Uploading file...", true);
                
                new Thread(new Runnable() {
                        public void run() {
                             runOnUiThread(new Runnable() {
                                    public void run() {
                                    	messageText.setText("uploading started.....");
                                    }
                                });                      
                          
                             uploadFile(uploadFilePath + "" + uploadFileName);
                                                     
                        }
                      }).start();        
                }
            });
	}
		
	
	private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
	      if(Build.VERSION.SDK_INT >= 10){
	          try {
	              final Method  m = device.getClass().getMethod("createInsecureRfcommSocketToServiceRecord", new Class[] { UUID.class });
	              return (BluetoothSocket) m.invoke(device, MY_UUID);
	          } catch (Exception e) {
	          }
	      }
	      return  device.createRfcommSocketToServiceRecord(MY_UUID);
	  }
	
	@Override
	  public void onPause() {
	    super.onPause();
	   try     {
	      btSocket.close();
	    } catch (IOException e2) {
	      errorExit("Fatal Error", "In onPause() and failed to close socket." + e2.getMessage() + ".");
	    }
	  }
	
	private void checkBTState() {
	    // Check for Bluetooth support and then check to make sure it is turned on
	    // Emulator doesn't support Bluetooth and will return null
	    if(btAdapter==null) { 
	      errorExit("Fatal Error", "Bluetooth not support");
	    } else {
	      if (btAdapter.isEnabled()) {
	      } else {
	        //Prompt user to turn on Bluetooth
	        Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
	        startActivityForResult(enableBtIntent, 1);
	      }
	    }
	  }
	
	 private void errorExit(String title, String message){
		    Toast.makeText(getBaseContext(), title + " - " + message, Toast.LENGTH_LONG).show();
		    finish();
		  }
	 
	@Override
	  public void onResume() {
	    super.onResume();
	    BluetoothDevice device = btAdapter.getRemoteDevice(address);
		try {
			btSocket = createBluetoothSocket(device);
        	Toast.makeText(getApplicationContext(), "Socket Created", Toast.LENGTH_SHORT).show();
		} catch (IOException e) {
			Toast.makeText(getApplicationContext(), "Error in Socket Creation", Toast.LENGTH_SHORT).show();
		}
		
		try {
		      btSocket.connect();
		      Toast.makeText(getApplicationContext(), "Socket Connected", Toast.LENGTH_SHORT).show();
		    } catch (IOException e) {
		    	Toast.makeText(getApplicationContext(), "Error in Socket Connection", Toast.LENGTH_SHORT).show();
		      
		    	try {
		        btSocket.close();
		      } catch (IOException e2) {
		    	  Toast.makeText(getApplicationContext(), "Socket Closed", Toast.LENGTH_SHORT).show();
		      }
		    }
		mConnectedThread = new ConnectedThread(btSocket);
	    mConnectedThread.start();
	}
	
	
	
	private class ConnectedThread extends Thread {
	    private final InputStream mmInStream;
	    public ConnectedThread(BluetoothSocket socket){
	        InputStream tmpIn = null;
	        // Get the input and output streams, using temp objects because
	        // member streams are final
	        try {
	            tmpIn = socket.getInputStream();
	        } catch (IOException e) { }
	 
	        mmInStream = tmpIn;
	    }
	 
	    public void run() {
	        byte[] buffer = new byte[10485760];  // buffer store for the stream
	        int bytes; // bytes returned from read()

	        // Keep listening to the InputStream until an exception occurs
	        while (true) {
	        	try {
	                // Read from the InputStream
	                bytes = mmInStream.read(buffer);		// Get number of bytes and message in "buffer"
                    h.obtainMessage(RECIEVE_MESSAGE, bytes, -1, buffer).sendToTarget();		// Send to message queue Handler
	            } catch (IOException e) {
	                break;
	            }
	        }
	    }
	}
	protected void onActivityResult(int requestCode, int resultCode, Intent data){
	    switch(requestCode) 
	    {
	    case (RESULT_OK):
	    {   
	      String name = data.getStringExtra("Bluetooth Enabled");
	      Toast.makeText(this, "You have chosen the book: " + " " + name,Toast.LENGTH_LONG).show();
	      break;
	    }
	    case (RESULT_CANCELED):
	    {	String name = data.getStringExtra("Bluetooth Not Enabled");
	    	Toast.makeText(this, "You have chosen the book: " + " " + name,Toast.LENGTH_LONG).show();
	    	break; 
	    }}}
	
	 public int uploadFile(String sourceFileUri) {
         
   	  
   	  String fileName = sourceFileUri;

         HttpURLConnection conn = null;
         DataOutputStream dos = null;  
         String lineEnd = "\r\n";
         String twoHyphens = "--";
         String boundary = "*****";
         int bytesRead, bytesAvailable, bufferSize;
         byte[] buffer;
         int maxBufferSize = 1 * 1024 * 1024; 
         File sourceFile = new File(sourceFileUri); 
         
         if (!sourceFile.isFile()) {
       	  
	           dialog.dismiss(); 
	           
	           Log.e("uploadFile", "Source File not exist :"
	        		               +uploadFilePath + "" + uploadFileName);
	           
	           runOnUiThread(new Runnable() {
	               public void run() {
	            	   messageText.setText("Source File not exist :"
	            			   +uploadFilePath + "" + uploadFileName);
	               }
	           }); 
	           
	           return 0;
          
         }
         else
         {
	           try { 
	        	   
	            	 // open a URL connection to the Servlet
	               FileInputStream fileInputStream = new FileInputStream(sourceFile);
	               URL url = new URL(upLoadServerUri);
	               
	               // Open a HTTP  connection to  the URL
	               conn = (HttpURLConnection) url.openConnection(); 
	               conn.setDoInput(true); // Allow Inputs
	               conn.setDoOutput(true); // Allow Outputs
	               conn.setUseCaches(false); // Don't use a Cached Copy
	               conn.setRequestMethod("POST");
	               conn.setRequestProperty("Connection", "Keep-Alive");
	               conn.setRequestProperty("ENCTYPE", "multipart/form-data");
	               conn.setRequestProperty("Content-Type", "multipart/form-data;boundary=" + boundary);
	               conn.setRequestProperty("uploaded_file", fileName); 
	               
	               dos = new DataOutputStream(conn.getOutputStream());
	     
	               dos.writeBytes(twoHyphens + boundary + lineEnd); 
	               dos.writeBytes("Content-Disposition: form-data; name=\"uploaded_file\";filename=\""
	            		                     + fileName + "\"" + lineEnd);
	               
	               dos.writeBytes(lineEnd);
	     
	               // create a buffer of  maximum size
	               bytesAvailable = fileInputStream.available(); 
	     
	               bufferSize = Math.min(bytesAvailable, maxBufferSize);
	               buffer = new byte[bufferSize];
	     
	               // read file and write it into form...
	               bytesRead = fileInputStream.read(buffer, 0, bufferSize);  
	                 
	               while (bytesRead > 0) {
	            	   
	                 dos.write(buffer, 0, bufferSize);
	                 bytesAvailable = fileInputStream.available();
	                 bufferSize = Math.min(bytesAvailable, maxBufferSize);
	                 bytesRead = fileInputStream.read(buffer, 0, bufferSize);   
	                 
	                }
	     
	               // send multipart form data necesssary after file data...
	               dos.writeBytes(lineEnd);
	               dos.writeBytes(twoHyphens + boundary + twoHyphens + lineEnd);
	     
	               // Responses from the server (code and message)
	               serverResponseCode = conn.getResponseCode();
	               String serverResponseMessage = conn.getResponseMessage();
	                
	               Log.i("uploadFile", "HTTP Response is : " 
	            		   + serverResponseMessage + ": " + serverResponseCode);
	               
	               if(serverResponseCode == 200){
	            	   
	                   runOnUiThread(new Runnable() {
	                        public void run() {
	                        	
	                        	String msg = "File Upload Completed.\n\n See uploaded file here : \n\n"
	                        		          +"http://169.254.91.111/uploads/"
	                        		          +uploadFileName;
	                        	
	                        	messageText.setText(msg);
	                            Toast.makeText(MainActivity.this, "File Upload Complete.", 
	                            		     Toast.LENGTH_SHORT).show();
	                        }
	                    });                
	               }    
	               
	               //close the streams //
	               fileInputStream.close();
	               dos.flush();
	               dos.close();
	                
	          } catch (MalformedURLException ex) {
	        	  
	              dialog.dismiss();  
	              ex.printStackTrace();
	              
	              runOnUiThread(new Runnable() {
	                  public void run() {
	                	  messageText.setText("MalformedURLException Exception : check script url.");
	                      Toast.makeText(MainActivity.this, "MalformedURLException", Toast.LENGTH_SHORT).show();
	                  }
	              });
	              
	              Log.e("Upload file to server", "error: " + ex.getMessage(), ex);  
	          } catch (Exception e) {
	        	  
	              dialog.dismiss();  
	              e.printStackTrace();
	              
	              runOnUiThread(new Runnable() {
	                  public void run() {
	                	  messageText.setText("Got Exception : see logcat ");
	                      Toast.makeText(MainActivity.this, "Got Exception : see logcat ", 
	                    		  Toast.LENGTH_SHORT).show();
	                  }
	              });
	              Log.e("Upload file to server Exception", "Exception : " 
	            		                           + e.getMessage(), e);  
	          }
	          dialog.dismiss();       
	          return serverResponseCode; 
	          
          } // End else block 
        } 
		
}
