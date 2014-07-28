package com.example.background;

import android.app.Activity;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;

public class Bg extends Activity{
	MediaPlayer ourSong;
	@Override
	protected void onCreate(Bundle Pss) {
		super.onCreate(Pss);
		setContentView(R.layout.bg);
		 ourSong=MediaPlayer.create(Bg.this,R.raw.ring);
		 ourSong.start();
         Thread timer=new Thread(){
        	 public void run(){
        		 
        	 try{
        		 sleep(5000);
        	 }catch(InterruptedException e){
        		 e.printStackTrace();
        	 }finally{
        		 Intent openStartingPoint=new Intent ("com.example.background.Menu");
        		 startActivity(openStartingPoint);
        		 
        	 }
        	 }
         };timer.start();
	}

	@Override
	protected void onPause() {
		super.onPause();
		ourSong.release();
		finish();
	}

}
