from pyglet import *
from random import randint, uniform
import numpy as np

window = window.Window(width=1000, height=750, caption="Author@Tharald")
batch = graphics.Batch()


n = 100
maxRadius = 22
minRadius = 2

posX = np.array([uniform(maxRadius, window.width-maxRadius) for _ in range(n)])
posY = np.array([uniform(maxRadius, window.height-maxRadius) for _ in range(n)])
velX = np.array([uniform(50, -50) for _ in range(n)])
velY = np.array([uniform(50, -50) for _ in range(n)])

weights = np.array([randint(minRadius, maxRadius) for _ in range(n)])


disks = [shapes.Circle(0,
                       0,
                       radius=weights[i],
                       batch=batch,
                       color=(randint(50, 255), randint(50, 255), randint(50, 255)))
         for i in range(n)]


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


def move(i, overlap, unit_normal):
    global posX, posY
    posX[i] -= overlap * unit_normal[0] / 2
    posY[i] += overlap * unit_normal[1] / 2


def update(dt):
    global posX, posY, velX, velY

    for index, disk in enumerate(disks):
        disk.x = posX[index]
        disk.y = posY[index]

    posX += velX * dt
    posY += velY * dt

    # Calculating vectors from disks using meshgrid.
    x_mesh, y_mesh = np.meshgrid(posX, posY)
    disp = np.dstack((x_mesh - x_mesh.T, y_mesh - y_mesh.T))

    # Calculating distances using dot product.
    dist = np.sqrt(np.einsum('...i,...i', disp, disp))

    # Finding colliding disks.
    collisions = np.where(dist < radii)

    # Stacking indices into pairs of 2.
    collisions_indices = np.column_stack((collisions[0], collisions[1]))

    # Sorting and getting only unique collisions.
    collisions_indices = np.unique(np.sort(collisions_indices, axis=1), axis=0)

    for i, j in collisions_indices:
        # Finding overlap, unit normal vector and unit tangent vector.
        overlap = dist[j, i] - (radii[i, j])
        unit_normal = disp[j, i] / (radii[i, j])

        unit_tangent = np.array([-unit_normal[1], unit_normal[0]])

        # Creating initial velocity vectors.
        vel_i = np.array([velX[i], velY[i]])
        vel_j = np.array([velX[j], velY[j]])

        # Projecting the velocity vectors onto the unit normal and unit tangent vectors.
        scalar_vel_i = np.dot(unit_normal, vel_i)
        scalar_vel_j = np.dot(unit_normal, vel_j)
        scalar_tan_i = np.dot(unit_tangent, vel_i)

        # New Normal velocities after collision.
        vel_i_after = (scalar_vel_i * (weights[i] - weights[j]) + 2 * weights[j] * scalar_vel_j) / radii[i, j]
        vel_j_after = (scalar_vel_j * (weights[j] - weights[i]) + 2 * weights[i] * scalar_vel_i) / radii[i, j]

        # Convert the scalar normal and tangential velocities into vectors.
        vel_i = vel_i_after * unit_normal
        vel_j = vel_j_after * unit_normal
        tan_i = scalar_tan_i * unit_tangent

        # Finding the final velocity vectors by adding the normal and tangential components + friction.
        new_vel_i = (vel_i + tan_i)
        new_vel_j = (vel_j + tan_i)
        velX[i], velY[i] = new_vel_i[0], new_vel_i[1]
        velX[j], velY[j] = new_vel_j[0], new_vel_j[1]

        # Moving the disks in the unit_normal direction until they don't overlap anymore.
        move(i, overlap, unit_normal)
        move(j, overlap, -unit_normal)


@window.event
def on_draw():
    window.clear()
    batch.draw()


clock.schedule_interval(update, 1/120)
app.run()
