import socket
import numpy as np
import time
HOST = 'localhost'  # Symbolic name meaning the local host
PORT = 114 # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))
T = 0.05
fs=5000;
nsamples = T * fs
t = np.linspace(0, T, nsamples, endpoint=False)
a = 2
f0 = 100
x = a * np.sin(2 * np.pi * f0 * t)
l=len(x);
i=0;
while True:
    if(i<l):
        s.send(str(x[i]))
        i=i+1;
    if(i==l):
        i=0;
    reply = s.recv(1024)
    if reply=='Quit':
        break
