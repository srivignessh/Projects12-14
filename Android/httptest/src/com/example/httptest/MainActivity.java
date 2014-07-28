package com.example.httptest;

import java.io.IOException;
import java.io.UnsupportedEncodingException;

import org.apache.http.client.ClientProtocolException;


import java.util.ArrayList;
import java.util.List;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;


import org.apache.http.NameValuePair;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.message.BasicNameValuePair;

// import everything you need
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class MainActivity extends Activity {

    Button sendButton;
 
    EditText msgTextField;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        // load the layout
        setContentView(R.layout.activity_main);        

        // make message text field object
        msgTextField = (EditText) findViewById(R.id.msgTextField);
        // make send button object
        sendButton = (Button) findViewById(R.id.sendButton);

    }

    // this is the function that gets called when you click the button
    public void send(View v) throws ClientProtocolException, IOException
    {
        // get the message from the message text box
        String msg = msgTextField.getText().toString();  
        List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(1);
	    nameValuePairs.add(new BasicNameValuePair("message", msg));
	       
        // make sure the fields are not empty
        if (msg.length()>0)
        {
	  	    HttpClient httpclient = new DefaultHttpClient();
	   	    HttpPost httppost = new HttpPost("http://192.168.80.1/test/test.php");
	   	    httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
	   	    httpclient.execute(httppost);
      	 
        }
        else
        {
        	// display message if text fields are empty
            Toast.makeText(getBaseContext(),"All field are required",Toast.LENGTH_SHORT).show();
        }

    }
    
}
