import matplotlib.pyplot as plt
import numpy as np
def animate_frames(frames):
    nBins   = frames.shape[0]
    frame   = frames[0]
    tempCS1 = plt.imshow(frame, cmap=plt.cm.gray)
    for k in range(nBins):
        frame   = frames[k]
        tempCS1 = plt.imshow(frame, cmap=plt.cm.gray)
        del tempCS1
        fig.canvas.draw()
        #time.sleep(1e-2) #unnecessary, but useful
        fig.clf()

fig = plt.figure()
ax  = fig.add_subplot(111)

win = fig.canvas.manager.window
fig.canvas.manager.window.after(100, animate_frames, frames)
