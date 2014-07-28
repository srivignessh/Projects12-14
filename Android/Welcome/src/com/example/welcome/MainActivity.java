package com.example.welcome;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {
	int counter;
	Button Add;
	TextView Display;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        counter=0;
        Add=(Button)findViewById(R.id.bAdd);
        Display=(TextView)findViewById(R.id.tvDisp);
        Add.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				counter++;	
				Display.setText("Total " + counter);
			}
		})   ; 
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
