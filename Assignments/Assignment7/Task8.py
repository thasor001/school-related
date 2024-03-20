from pyglet import *
import numpy as np
from random import uniform

window = window.Window(height=750, width=1000)

n = 50

disks = np.array([np.array([
        uniform(175, window.width-175),  # X
        uniform(175, window.height-175),  # Y
    ])for _ in range(n)])

weight = np.array([uniform(5, 10)for _ in range(n)])
weights = np.meshgrid(weight, weight)
weights = weights[0]
vel = np.zeros((n, 2))

def gravity(dt):
    global vel, weights, disks
    x_mesh, y_mesh = np.meshgrid(disks[:, 0], disks[:, 1])

    disp = np.dstack((x_mesh - x_mesh.T, y_mesh - y_mesh.T))
    dist = np.sqrt(np.sum(disp ** 2, axis=2))
    vel += dt*np.sum(np.nan_to_num((-15 * weights.reshape(n**2, 1))/(dist.reshape(n**2, 1)**2) * disp.flatten().reshape(n**2, 2)).reshape(n, -1, 2)[:, :, :], axis=1)
    disks += vel * dt


@window.event()
def on_draw():
    window.clear()
    for i in range(n):
        shapes.Circle(x=disks[i][0], y=disks[i][1], radius=weights[0, i]).draw()


clock.schedule_interval(gravity, 1/30)
app.run()
