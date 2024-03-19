from pyglet import *
import numpy as np
from random import uniform

window = window.Window(height=750, width=1000)

n = 4

disks = np.array([np.array([
        uniform(175, window.width-175),  # X
        uniform(175, window.height-175),  # Y
    ])for _ in range(n)])

x_mesh, y_mesh = np.meshgrid(disks[:, 0], disks[:, 1])

disp = np.dstack((x_mesh - x_mesh.T, y_mesh - y_mesh.T))
dist = np.sqrt(np.sum(disp**2, axis=2))

weight = np.array([uniform(5, 10)for _ in range(n)])
weights = np.meshgrid(weight, weight)
weights = weights[0] * weight[1]
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

def gravity(dt):
    global vel, weights, dist, disks
    vel = vel + np.sum((dt * -10 * weights)/(dist**2) * disp[:, :], axis=0)
    disks[:, :] = disks[:, :] + vel[:, :] * dt


@window.event()
def on_draw():
    window.clear()
    for i in range(n):
        if i == 0:
            shapes.Circle(x=disks[i][0], y=disks[i][1], radius=weights[i, 0], color=(255, 0, 0)).draw()
        else:
            shapes.Circle(x=disks[i][0], y=disks[i][1], radius=weights[i, 0], color=(0, 0, 255)).draw()

clock.schedule_interval(gravity, 1/60)
app.run()
