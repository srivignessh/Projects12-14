# Say anything you type, and write anything you say.
# Stops when you say "turn off" or type "turn off".

import speech
#import sys
#script, filename = sys.argv
txt = open('hell.txt')
def callback(phrase, listener):
    print ": %s" % phrase
    if phrase == "turn off":
        speech.say("Goodbye.")
        listener.stoplistening()
        sys.exit()
listener = speech.listenforanything(callback)
while listener.islistening():
    speech.say(txt.read())
    if(not txt.read()):
        listener.stoplistening()
        sys.exit()
