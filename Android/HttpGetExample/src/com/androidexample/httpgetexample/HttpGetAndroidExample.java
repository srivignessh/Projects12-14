package com.androidexample.httpgetexample;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import org.apache.http.client.HttpClient;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.View;
import android.widget.Button;  
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class HttpGetAndroidExample extends Activity {

	TextView content;
	EditText fname,email,login,pass;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_http_get_android_example);
		
		content = (TextView)findViewById(R.id.content);
        fname	= (EditText)findViewById(R.id.name);
        email	= (EditText)findViewById(R.id.email);
        login	= (EditText)findViewById(R.id.loginname);
        pass	= (EditText)findViewById(R.id.password);
        Button saveme=(Button)findViewById(R.id.save);
		
		
		saveme.setOnClickListener(new Button.OnClickListener(){
        	public void onClick(View v)
        	{	
        		//ALERT MESSAGE
				Toast.makeText(getBaseContext(),
						"Please wait, connecting to server.",
						Toast.LENGTH_LONG).show();
			try{	
				
				String loginValue = URLEncoder.encode(login.getText().toString(), "UTF-8");
				String fnameValue = URLEncoder.encode(fname.getText().toString(), "UTF-8");
				String emailValue = URLEncoder.encode(email.getText().toString(), "UTF-8");
				String passValue  = URLEncoder.encode(pass.getText().toString(), "UTF-8");
				
					HttpClient Client = new DefaultHttpClient();
					String URL = "http://androidexample.com/media/webservice/httpget.php?user="+loginValue+
					"&name="+fnameValue+"&email="+emailValue+"&pass="+passValue;
					
					//Log.i("httpget", URL);
			    	try
			    	{
			    		HttpGet httpget = new HttpGet(URL);
			            ResponseHandler<String> responseHandler = new BasicResponseHandler();
			            
			            String SetServerString = "";
			            SetServerString = Client.execute(httpget, responseHandler);
			            content.setText(SetServerString);
			    	}
			    	catch(Exception ex)
			    	{
			    		content.setText("Fail!");
			    	}
				}
		    	catch(UnsupportedEncodingException ex)
		    	{
		    		content.setText("Fail111");
		    	}  	 	
        	}
        });  
	}
}
