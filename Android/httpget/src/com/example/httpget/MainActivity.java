package com.example.httpget;

import android.app.Activity;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {
	 
    TextView content;
    EditText fname,email,login,pass;

@Override
protected void onCreate(Bundle savedInstanceState) {

          super.onCreate(savedInstanceState);
         setContentView(R.layout.activity_main);

         content   =  (TextView)findViewById(R.id.content);
         fname     =  (EditText)findViewById(R.id.name);
         email      =  (EditText)findViewById(R.id.email);
         login       =  (EditText)findViewById(R.id.loginname);
         pass       =  (EditText)findViewById(R.id.password);

       Button saveme=(Button)findViewById(R.id.save);


saveme.setOnClickListener(new Button.OnClickListener(){
  public void onClick(View v)
   { 
              //ALERT MESSAGE
             Toast.makeText(getBaseContext(),"Please wait, connecting to server.",Toast.LENGTH_LONG).show();

    try{ 

         // URLEncode user defined data

           String loginValue    = URLEncoder.encode(login.getText().toString(), "UTF-8");
           String fnameValue  = URLEncoder.encode(fname.getText().toString(), "UTF-8");
           String emailValue   = URLEncoder.encode(email.getText().toString(), "UTF-8");
           String passValue    = URLEncoder.encode(pass.getText().toString(), "UTF-8");

        // Create http cliient object to send request to server

           HttpClient Client = new DefaultHttpClient();
        
        // Create URL string

         String URL = "http://androidexample.com/media/webservice/httpget.php?user="+loginValue+"&name="+fnameValue+"&email="+emailValue+"&pass="+passValue;

        //Log.i("httpget", URL);

       try
        {
                      String SetServerString = "";
            
                    // Create Request to server and get response
            
                      HttpGet httpget = new HttpGet(URL);
                     ResponseHandler<String> responseHandler = new BasicResponseHandler();
                     SetServerString = Client.execute(httpget, responseHandler);
           
                      // Show response on activity 

                     content.setText(SetServerString);
         }
       catch(Exception ex)
          {
                 content.setText("Fail!");
           }
    }
  catch(UnsupportedEncodingException ex)
   {
           content.setText("Fail");
    }     
}
});  
}
}