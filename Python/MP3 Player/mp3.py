import os, string
import mp3play
import time
setpath =r"D:\Music" #This can be hard coded.
for root, dirs, files in os.walk(setpath, topdown=False):
	for fname in files:
		s = string.find(fname, '.mp3')
		if s >=1:
			fpath = os.path.join(root,fname)
			print "Playing", fname
			clip = mp3play.load(fpath)
		
			clip.play()
			time.sleep(5)
			clip.stop()
