package com.example.savefiledemo;

import android.os.Bundle;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.widget.TextView;

import java.io.FileReader;
import java.io.FileWriter;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		createFile();
		String file_contents = readFile();
		TextView tv = (TextView)findViewById(R.id.tv);
		tv.setText("Read File contents from SDCARD : n" + file_contents);
	}
	 @SuppressLint("SdCardPath")
	public void createFile(){
	        FileWriter fWriter;
	        try{
	             fWriter = new FileWriter("/sdcard/myfile.txt");
	             fWriter.write("My file contents");
	             fWriter.flush();
	             fWriter.close();
	         }catch(Exception e){
	                  e.printStackTrace();
	         }
	    }
	 @SuppressLint("SdCardPath")
	@SuppressWarnings("resource")
	public String readFile(){
	        char buf[] = new char[512];
	        FileReader rdr;
	        String contents = "";
	        try {
	            rdr = new FileReader("/sdcard/myfile.txt");
	            int s = rdr.read(buf);
	            for(int k = 0; k < s; k++){
	                contents+=buf[k];
	            }
	        } catch (Exception e) {
	            e.printStackTrace();
	        }
	        return contents;
	    }
}