from pyglet import *
from random import randint, uniform
import numpy as np
from time import time


window = window.Window(width=1000, height=750, caption="Author@Tharald")

batch = graphics.Batch()

n = 100

weights = np.array([randint(2, 22) for _ in range(n)])

bitMap = np.zeros((n, n), dtype=bool)

disks = np.array([
    shapes.Circle(x=0,
                  y=0,
                  radius=weights[i],
                  batch=batch)
    for i in range(n)])

pos = np.array([[
        uniform(22, window.width-22),
        uniform(22, window.height-22)]
    for _ in range(n)])

vel = np.array([np.array([
    uniform(-50, 50), uniform(-50, 50)
])for _ in range(n)])

# I make the weights into a colum vector containing one of the different elements each
# Example. original = [1,2,3] new = [[1], [2], [3]]
# I do this so that I can make it into a (100, 100) shape like the dist array later.
# new shape of col_vec is (100, 1)
col_vec = weights[:, np.newaxis]


# By plussing col_vec with the original weights I get a shape of (100, 100).
# Example. original = [0, 4, 7] next step = [[0], [4], [7]] final = [[0, 4, 7], [4, 8, 11], [7, 11, 14]]
# This new array becomes the combined radius's of the disks.
# Example dist[0] = [[0,2, 6], [2, 0, 3], [6, 3, 0]] then the new weights[0,0] (radii) for dist[0,0] would be first the
# radius of itself + itself, then itself + disk2 then itself + disk3, if dist[0, :] < radii[0, :] then collision.
radii = col_vec + weights

# We do this since a disk's radius will + with itself and result in for instance: a combined radius of 20.
# while the distance between itself and itself will be 0 this will then tell the machine
# that there is a collision here since 0 < 20.
# we don't want that, therefore we make the disk + itself = 0 then 0(Dist) < 0(radii) = False
np.fill_diagonal(radii, 0)

# Fastest way i could find to create vectors between all points was this:
# x_mesh, y_mesh = np.meshgrid(pos[:, 0], pos[:, 1])
# disp = np.dstack((x_mesh - x_mesh.T, y_mesh - y_mesh.T))

# All tests were done with a for loop(n = 100):
# Calculating distances, Fastest way I could find.
# dist = np.sqrt(np.einsum('...i,...i', disp, disp)) took 0.004 seconds,
# dist = np.sqrt(np.sum(disp**2, axis=2)) took 0.009,
# dist = np.linalg.norm(disp, axis=2) took 0.012 seconds.

# Checking time of 1 iteration (as long as it's under 0.16 we good :) )
average_time = 0
for _ in range(n):
    start_time = time()

    for index, disk in enumerate(disks):
        disk.x = pos[index, 0]
        disk.y = pos[index, 1]

    pos[:] += vel[:] * 0

    test_x_mesh, test_y_mesh = np.meshgrid(pos[:, 0], pos[:, 1])
    test_disp = np.dstack((test_x_mesh - test_x_mesh.T, test_y_mesh - test_y_mesh.T))
    test_dist = np.sqrt(np.einsum('...i,...i', test_disp, test_disp))

    # Checking for collisions
    collisions = np.where(test_dist < radii)

    collisions_indices = np.column_stack((collisions[0], collisions[1]))

    # Sort each pair of indices
    collisions_indices = np.sort(collisions_indices, axis=1)

    # Keep only unique pairs
    collisions_indices = np.unique(collisions_indices, axis=0)

    # Handeling the collisions
    for i, j in collisions_indices:
        Un = test_disp[i, j] / test_dist[i, j]
        pos[i] += (radii[i, j] - test_dist[i, j]) * Un / 2
        pos[j] -= (radii[i, j] - test_dist[i, j]) * Un / 2
        tan = np.array([-Un[1], Un[0]])
        vel1n = Un[0] * vel[i, 0] + Un[1] * vel[i, 1]
        vel2n = Un[0] * vel[j, 0] + Un[1] * vel[j, 1]
        vel1t = tan[0] * vel[i, 0] + tan[1] * vel[i, 1]
        vel2t = tan[0] * vel[j, 0] + tan[1] * vel[j, 1]
        newvel1n = (vel1n * (weights[i] - weights[j]) + 2 * weights[j] * vel2n) / radii[i, j]
        newvel2n = (vel2n * (weights[j] - weights[i]) + 2 * weights[i] * vel1n) / radii[j, i]
        vel1n = newvel1n * Un
        vel2n = newvel2n * Un
        newvel1t = vel1t * tan
        newvel2t = vel2t * tan
        vel[i] = vel1n + newvel1t
        vel[j] = vel2n + newvel2t

    end_time = time()
    average_time += end_time - start_time

print("One Iteration takes : ", average_time/n, " Seconds to complete")

def update(dt):
    global pos, radii
    # Updating all disks positions.
    for index, disk in enumerate(disks):
        disk.x = pos[index, 0]
        disk.y = pos[index, 1]

    # Updating Pos array with velocity * dt.
    pos += vel * dt

    # Calculating vectors from disks using meshgrid.
    x_mesh, y_mesh = np.meshgrid(pos[:, 0], pos[:, 1])
    disp = np.dstack((x_mesh - x_mesh.T, y_mesh - y_mesh.T))

    # Calculating distances using dot product.
    dist = np.sqrt(np.einsum('...i,...i', disp, disp))

    # Checking for collisions
    collisions = np.where(dist < radii)

    # Stacking them in pairs of 2.
    collisions_indices = np.column_stack((collisions[0], collisions[1]))

    # Sort each pair of indices
    collisions_indices = np.sort(collisions_indices, axis=1)

    # Keep only unique pairs
    collisions_indices = np.unique(collisions_indices, axis=0)


    # Handeling the collisions
    for i, j in collisions_indices:
        Un = disp[i, j] / dist[i, j]
        pos[i] += (radii[i, j] - dist[i, j]) * Un / 2
        pos[j] -= (radii[i, j] - dist[i, j]) * Un / 2
        tan = np.array([-Un[1], Un[0]])
        vel1n = Un[0] * vel[i, 0] + Un[1] * vel[i, 1]
        vel2n = Un[0] * vel[j, 0] + Un[1] * vel[j, 1]
        vel1t = tan[0] * vel[i, 0] + tan[1] * vel[i, 1]
        vel2t = tan[0] * vel[j, 0] + tan[1] * vel[j, 1]
        newvel1n = (vel1n * (weights[i] - weights[j]) + 2 * weights[i] * vel2n) / radii[i, j]
        newvel2n = (vel2n * (weights[j] - weights[i]) + 2 * weights[j] * vel1n) / radii[i, j]
        vel1n = newvel1n * Un
        vel2n = newvel2n * Un
        newvel1t = vel1t * tan
        newvel2t = vel2t * tan
        vel[i] = vel1n + newvel1t
        vel[j] = vel2n + newvel2t


@window.event
def on_draw():
    window.clear()
    batch.draw()


clock.schedule_interval(update, 1/60)
app.run()
