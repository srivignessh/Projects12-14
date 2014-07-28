import Leap, sys
import time,math
import pygame
from pygame.locals import *
   
class LeapListener(Leap.Listener):
    def on_init(self, controller):
        print "Initialized"
    def on_connect(self, controller):
        print "Connected"
    def on_disconnect(self, controller):
        print "Disconnected"
    def on_exit(self, controller):
        print "Exited"
    def on_frame(self,controller):
        self.frame=controller.frame()
        
def clean_background(screen):
    background = pygame.Surface(screen.get_size())
    background.fill((255,255,255))
    background = background.convert()
    return background

def main():

    leap = LeapListener()
    controller = Leap.Controller()
    controller.add_listener(leap)
    pygame.init()
    size=(800,600)
    screen=pygame.display.set_mode(size,0,24)
    pygame.display.set_caption("Leap Test")
    bkg=clean_background(screen)
    screen.blit(bkg,(0,0))
    pygame.display.flip()
    time.sleep(2)
    run=True
    while run:
       pressed=pygame.key.get_pressed()
       for event in pygame.event.get():
          if event.type==QUIT or pressed[K_q]:
              controller.remove_listener(leap)
              pygame.quit()
              sys.exit()
              run=False
          elif pressed[K_a]:
              bkg=clean_background(screen)
          elif pressed[K_s]:
              print 'save'
       frame=leap.frame
       if not frame.hands.is_empty:
            hand=frame.hands
            fingers = hand[0].fingers
            if not fingers.is_empty:
                    p=fingers[0].tip_position
                    x=int(400+2*p.x)
                    y=int(1000-2*p.y)
                    print x,y,len(fingers)
                    if(len(hand)<2):
                        pygame.draw.circle(bkg, (255,0,0),(x,y), 10)
                    else:
                        pygame.draw.circle(bkg, (0,0,255),(x,y), 10)
       screen.blit(bkg,(0,0))
       pygame.display.flip()
if __name__=='__main__':
    main()

