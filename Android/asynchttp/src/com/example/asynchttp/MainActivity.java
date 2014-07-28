
package com.example.asynchttp;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.Toast;

import com.loopj.android.http.*;
public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		AsyncHttpClient client = new AsyncHttpClient();
		client.get("http://www.google.com", new AsyncHttpResponseHandler() {
		    @Override
		    public void onSuccess(String response) {
		    	Toast.makeText(getBaseContext(),response,Toast.LENGTH_LONG).show();
		    }
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
