from pyglet import *
import numpy as np
from random import uniform
from time import time
from math import sqrt

window = window.Window(height=1000, width=1000)

n = 2

disks = np.array([np.array([
        uniform(100, window.height-100),  # X
        uniform(100, window.width-100),  # Y
    ])for _ in range(n)])

disp = disks.reshape(n, 1, 2) - disks
dist = np.sqrt(np.sum(disp**2, axis=2))

print(disks)
print("_________________--__________ Vector")
print(disp)
print("_________________--__________ Distance")
print(dist)

weight = np.array([uniform(5, 10)for _ in range(n)])
vel = np.array([np.array([0., 0.])for _ in range(n)])



def gravity(dt):
    pass



@window.event()
def on_draw():
    window.clear()


start = time()
disp2 = (10, 2)
for _ in range(1):
    pass

end = time()
#print(end - start)

clock.schedule_interval(gravity, 1/60)
app.run()
