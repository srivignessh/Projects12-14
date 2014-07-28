import time
from threading import Timer

def poll_port():
    print "Getting my data from port", time.time()

def main():
    print "Main:enter", time.time()
    while True:
        t = Timer(5, poll_port)
        t.start()
        t.join()
        print "after join:", time.time()

if __name__ == "__main__":
    main()
