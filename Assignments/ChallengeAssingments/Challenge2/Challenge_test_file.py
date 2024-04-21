from pyglet import *
from random import randint, uniform
import numpy as np
from pyglet.window import FPSDisplay, key, mouse

window = window.Window(width=300, height=500, caption="Author@Tharald")
batch = graphics.Batch()

MAX = 151
scroll = 0
mouse_pos = (0, 0)

n = 150
radius = 5
init_speed = 1

momentum_loss = -0.65
friction = 0.9
gravity = 200.

count = 0

posX = np.array([uniform(radius, window.width-radius) for _ in range(n)])
posY = np.array([uniform(radius, window.height-radius) for _ in range(n)])
velX = np.array([uniform(50, -50) * init_speed for _ in range(n)])
velY = np.array([uniform(50, -50) * init_speed for _ in range(n)])

weights = np.array([radius for _ in range(n)])

bitMap = np.zeros(5, dtype=bool)

disks = [shapes.Circle(0,
                       0,
                       radius=weights[i],
                       batch=batch,
                       color=(randint(50, 255), randint(50, 255), randint(50, 255)))
         for i in range(n)]

num_shapes = text.Label(text="Num shapes : " + str(n),
                        x=5,
                        y=window.height-10,
                        font_size=20,
                        anchor_y='center')


radii = weights[:, np.newaxis] + weights
np.fill_diagonal(radii, 0)

def menu():
    print("M - MENU")
    print("SCROLL UP, DOWN - Values up/down")
    print("N - New Disks")
    print("C - Clear all disks")
    print("G - Gravity (-200, 200)")


def clamp(value, minimum, maximum):
    if value < minimum:
        return minimum
    elif value > maximum:
        return maximum
    else:
        return value


@window.event
def on_key_press(symbol, modifiers):
    global bitMap, scroll

    if symbol == key.M:
        menu()
    elif symbol == key.G:
        print("Current Gravity : ", gravity)
        scroll = gravity
        bitMap[0] = True
    elif symbol == key.C:
        bitMap[1] = True
        print("Clearing shapes :")
    elif symbol == key.N:
        bitMap[2] = True


@window.event
def on_mouse_motion(x, y, dx, dy):
    global mouse_pos
    mouse_pos = (x, y)


@window.event
def on_key_release(symbol, modifiers):
    global bitMap, scroll

    if symbol == key.G:
        print("New Gravity : ", gravity)
        bitMap[0] = False
        scroll = 0  # Reset scroll value when the key is released
    elif symbol == key.N:
        bitMap[2] = False


@window.event
def on_mouse_scroll(x, y, scroll_x, scroll_y):
    global scroll
    scroll -= scroll_y * 5


def event_handler():
    global gravity, scroll, disks, posX, posY, velX, velY
    global weights, radii, num_shapes, n, count

    if bitMap[0]:
        scroll = clamp(scroll, -200., 200.)
        print("Value : ", scroll)
        gravity = scroll
    elif bitMap[1]:
        n = 0
        disks = []
        posX = np.array([])
        posY = np.array([])
        velX = np.array([])
        velY = np.array([])
        weights = np.array([])
        radii = np.array([])
        num_shapes = text.Label(text="Num shapes : " + str(n),
                                x=5,
                                y=window.height - 10,
                                font_size=20,
                                anchor_y='center')
        bitMap[1] = False
    elif bitMap[2]:
        if count == 0 and n < MAX:
            posX = np.append(posX, mouse_pos[0])
            posY = np.append(posY, mouse_pos[1])
            velX = np.append(velX, uniform(300, -300) * init_speed)
            velY = np.append(velY, uniform(300, -300) * init_speed)
            weights = np.append(weights, radius)
            disks.append(shapes.Circle(0, 0, radius=weights[len(weights) - 1], batch=batch,
                                       color=(randint(50, 255), randint(50, 255), randint(50, 255))))
            radii = weights[:, np.newaxis] + weights
            np.fill_diagonal(radii, 0)
            num_shapes = text.Label(text="Num shapes : " + str(n),
                                    x=5,
                                    y=window.height - 10,
                                    font_size=20,
                                    anchor_y='center')
            n += 1


def move(i, overlap, unit_normal):
    posX[i] -= overlap * unit_normal[0]
    posY[i] += overlap * unit_normal[1] * 3/4


def update(dt):
    global posX, posY, velX, velY, num_shapes, count

    count += dt
    if count >= 1/6:
        count = 0

    for index, disk in enumerate(disks):
        disk.x = posX[index]
        disk.y = posY[index]

    # Updating position based on velocity.
    posX += velX * dt
    posY += velY * dt

    # Moving Circles inside of screen.
    posXColL = np.where(posX < weights)[0]                  # L - Left
    posXColR = np.where(posX > window.width - weights)[0]   # R - Roof

    posYColG = np.where(posY < weights)[0]                  # G - Ground
    posYColR = np.where(posY > window.height - weights)[0]  # R - Right

    posX[posXColL] = radius
    posX[posXColR] = window.width - radius

    posY[posYColG] = radius
    posY[posYColR] = window.height - radius

    # Collisions with screen.
    velX[posXColL] *= momentum_loss       # They lose some momentum when they hit surfaces (not 100% elastic).
    velX[posXColR] *= momentum_loss
    velX[posYColG] *= friction            # They lose some momentum as well by friction.
    velX[posYColR] *= friction

    velY[posYColG] *= momentum_loss
    velY[posYColR] *= momentum_loss

    velX[abs(velX) < 0.0005] = 0

    # Collision resolution loop
    for _ in range(max(1, n//15)):

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
            overlap = dist[j, i] - (radius * 2)
            unit_normal = disp[j, i] / (radius * 2)

            unit_tangent = np.array([-unit_normal[1], unit_normal[0]])

            # Creating initial velocity vectors.
            vel_i = np.array([velX[i], velY[i]])
            vel_j = np.array([velX[j], velY[j]])

            # Projecting the velocity vectors onto the unit normal and unit tangent vectors.
            scalar_vel_i = np.dot(unit_normal, vel_i)
            scalar_vel_j = np.dot(unit_normal, vel_j)
            scalar_tan_i = np.dot(unit_tangent, vel_i)

            # New Normal velocities after collision.
            vel_i_after = scalar_vel_j
            vel_j_after = scalar_vel_i

            # Convert the scalar normal and tangential velocities into vectors.
            vel_i = vel_i_after * unit_normal
            vel_j = vel_j_after * unit_normal
            tan_i = scalar_tan_i * unit_tangent

            # Finding the final velocity vectors by adding the normal and tangential components + friction.
            new_vel_i = (vel_i + tan_i) * friction
            new_vel_j = (vel_j + tan_i) * friction
            velX[i], velY[i] = new_vel_i[0], new_vel_i[1]
            velX[j], velY[j] = new_vel_j[0], new_vel_j[1]

            # Moving the disks in the unit_normal direction until they don't overlap anymore.
            move(i, overlap, unit_normal)
            move(j, overlap, -unit_normal)

    # Updating velocity due to gravity.
    velY -= gravity * dt



@window.event
def on_draw():
    window.clear()
    batch.draw()
    num_shapes.draw()
    if np.any(bitMap):
        event_handler()


clock.schedule_interval(update, 1/120)
app.run()
