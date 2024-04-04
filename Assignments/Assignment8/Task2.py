from pyglet import *
import numpy as np
from random import uniform
from time import time


window = window.Window(1000, 750, caption="Author@Tharald")

batch = graphics.Batch()

disks = []

# Max number of disks
n = 1000

pos = np.array([[
    500.,
    375.
]for _ in range(n)])

vel = np.array([[
    uniform(-75, 75),
    uniform(0, 150)
]for _ in range(n)])

t = 0
direction = 1
wind_dir = 1


@window.event
def on_draw():
    window.clear()
    batch.draw()


def update(dt):
    global vel, pos, t, direction, wind_dir, disks

    # Updating pos.
    for index, disk in enumerate(disks):
        disk.x = pos[index, 0]
        disk.y = pos[index, 1]

    # Creating 5 disks every frame.
    for _ in range(5):
        if len(disks) < n:
            disks.append(shapes.Circle(radius=uniform(3, 15), x=500, y=375, batch=batch))

    # To see how many disks that are alive
    length = len(disks)

    # Updating pos based on velocity
    pos[:length] += vel[:length] * dt

    # Calculating wind force
    newvel = 100 * t

    # Wind (x), and gravity (y), 60 <- Gravity
    vel[:length] -= [newvel * wind_dir * dt, 60 * dt]

    # Checking if they are outside of bounds.
    outside = np.where(np.logical_or((pos[:length, 0] < 0),
                                     (pos[:length, 0] > 1000)
                                     | (pos[:length, 1] < 0))
                       )

    # Turning it from idarray (or something, not really sure what it is) into a normal array.
    outside = outside[0]

    print(outside)

    # Deleting the elements that correspond to the indexes found in outside.
    if len(outside) > 0:
        disks = [disks[i] for i in range(len(disks)) if i not in outside]
        pos = np.delete(pos, outside, axis=0)
        vel = np.delete(vel, outside, axis=0)
        for i in range(len(outside)):
            pos = np.insert(pos, n-len(outside)+i, np.array([[500., 375.]]), axis=0)
            vel = np.insert(vel, n-len(outside)+i, np.array([uniform(-75, 75), uniform(0, 150)]), axis=0)

    # Updating time.
    t += dt * direction/2

    if t > 1:
        t = 1
        direction *= -1
    elif t < 0:
        t = 0
        direction *= -1
        wind_dir *= -1


clock.schedule_interval(update, 1/60.0)
app.run()

