package com.example.background;

import java.util.Random;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.text.InputType;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.ToggleButton;

public class TextPly extends Activity{

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.text);
		Button chkCmd=(Button) findViewById(R.id.bResults);
		final ToggleButton passTog=(ToggleButton) findViewById(R.id.toggleButton1);
		final EditText input =(EditText) findViewById(R.id.etCommands);
		final TextView display=(TextView) findViewById(R.id.tvResults);
		passTog.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				if(passTog.isChecked()){
				 input.setInputType(InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD);
				}
				else{
					input.setInputType(InputType.TYPE_CLASS_TEXT );
				}
			}
		});
		chkCmd.setOnClickListener(new View.OnClickListener(){

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				String check=input.getText().toString();
				if(check.contentEquals("left")){
					display.setGravity(Gravity.LEFT);
				}else if(check.contentEquals("WTF")){
					Random crazy=new Random();
					display.setText("WTF{{");
					display.setTextSize(crazy.nextInt(75));
					display.setTextColor(Color.rgb(crazy.nextInt(175), crazy.nextInt(175), crazy.nextInt(175)));
					switch(crazy.nextInt(3)){
					case 0:
						display.setGravity(Gravity.LEFT);
						break;
					case 1:
						display.setGravity(Gravity.CENTER);
						break;
					case 2:
						display.setGravity(Gravity.RIGHT);
						break;
					}
				}else if(check.contentEquals("right")){
					display.setGravity(Gravity.RIGHT);
				}else if(check.contentEquals("blue")){
					display.setTextColor(Color.BLUE);
				}else{
					display.setGravity(Gravity.CENTER);
					display.setText("invalid");
				}
					
					
			}
			
		});
	}
	

}
