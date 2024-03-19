from pyglet import *
import numpy as np
from random import uniform

window = window.Window(height=750, width=1000)

n = 2

disks = np.array([np.array([
        uniform(175, window.width-175),  # X
        uniform(175, window.height-175),  # Y
    ])for _ in range(n)])

disp = disks.reshape(n, 1, 2) - disks
dist = np.sqrt(np.sum(disp**2, axis=2))

weights = np.array([uniform(5, 10)for _ in range(n)])
vel = np.zeros((n, 2))

print("_______X_____________Y_______ DISKS")
print(disks)
print("_______________1_____________ Vector DISP")
print(disp)
print("_______1_____________2_______ Distance DIST")
print(dist)
print("_______1_____________2_______ Weight")
print(weights)
print("_______1_____________2_______ Vel")
print(vel)
print("_____________________________ NEW VEL")
test = np.zeros((n, 2))

for i in range(n):
    vel[i, :] = ((0.2 * 50) * weights[weights != weights[i]] / (dist[i, dist[i] != 0] ** 2)) * disp[i, disp[i] != 0][0:2]

print(vel)

for i in range(n):
    test[0, :] += ((0.2*50) * weights[1] / (dist[0, 1]**2)) * disp[0, 1]

print(test)

def gravity(dt):
    global vel, weights, dist
    for i in range(n):
        #vel[i, :] = (dt*20 * weights[weights != weights[i]] / (dist[i, dist[i] != 0]**2)) * disp[i, disp[i] != 0][0:2]
        pass


@window.event()
def on_draw():
    window.clear()
    for i in range(n):
        shapes.Circle(x=disks[i][0], y=disks[i][1], radius=weights[i], color=(255, 0, 0)).draw()


clock.schedule_interval(gravity, 1/60)
app.run()
