from pyglet import *
from random import randint, uniform
import numpy as np
from pyglet.window import key

window = window.Window(height=600, width=1200, caption="Author@Tharald")
batch = graphics.Batch()

MAX = 601

n = 300
radius = 5
init_speed = 1.

momentum_loss = -0.65
friction = 0.9
gravity = 45.

speed = 50

posX = np.array([uniform(radius, window.width-radius) for i in range(n)])
posY = np.array([uniform(radius, window.height-radius) for _ in range(n)])

velX = np.array([uniform(speed, -speed) * init_speed for _ in range(n)])
velY = np.array([uniform(speed, -speed) * init_speed for _ in range(n)])

bitMap = np.zeros(4, dtype=bool)

grid_lines = []

for i in range(window.width // (radius * 2)):
    grid_lines.append(shapes.Line(x=i*(radius * 2), y=0, x2=i*(radius * 2), y2=window.height, batch=batch, color=(0, 255, 0, 100)))

for i in range(window.height // (radius * 2)):
    grid_lines.append(shapes.Line(x=0, y=i*(radius * 2), x2=window.width, y2=i*(radius * 2), batch=batch, color=(0, 255, 0, 100)))


disks = [
    shapes.Circle(0,
                  0,
                  radius=radius,
                  batch=batch,
                  color=(randint(50, 255), randint(50, 255), randint(50, 255)))
    for i in range(n)
]

num_shapes = text.Label(text="Num shapes : " + str(n),
                        x=5,
                        y=window.height-10,
                        font_size=20,
                        anchor_y='center')


def menu():
    print("M - MENU")
    print("SCROLL UP, DOWN - Values up/down")
    print("N - New Disks")
    print("C - Clear all disks")
    print("G - Gravity (-60, 60)")


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
    global weights, radii, num_shapes, n

    if bitMap[0]:
        scroll = clamp(scroll, -60., 60.)
        print("Value : ", scroll)
        gravity = scroll
    elif bitMap[1]:
        n = 0
        disks = []
        posX = np.array([])
        posY = np.array([])
        velX = np.array([])
        velY = np.array([])
        num_shapes = text.Label(text="Num shapes : " + str(n),
                                x=5,
                                y=window.height - 10,
                                font_size=20,
                                anchor_y='center')
        bitMap[1] = False
    elif bitMap[2]:
        if n < MAX:
            posX = np.append(posX, mouse_pos[0])
            posY = np.append(posY, mouse_pos[1])
            velX = np.append(velX, uniform(500, -500) * init_speed)
            velY = np.append(velY, uniform(500, -500) * init_speed)
            disks.append(shapes.Circle(0, 0, radius=radius, batch=batch,
                                       color=(randint(50, 255), randint(50, 255), randint(50, 255))))
            num_shapes = text.Label(text="Num shapes : " + str(n),
                                    x=5,
                                    y=window.height - 10,
                                    font_size=20,
                                    anchor_y='center')
            n += 1


def move(x, overlap, unit_normal):
    posX[x] += overlap * unit_normal[0]
    posY[x] += overlap * unit_normal[1] * 4/5


def collision_handler(i, j, unit_normal):
    # Creating the unit tangent vector.
    unit_tangent = np.array([-unit_normal[1], unit_normal[0]])

    # Creating initial velocity vectors.
    vel_i = np.array([velX[i], velY[i]])
    vel_j = np.array([velX[j], velY[j]])

    # Projecting the velocity vectors onto the unit normal and unit tangent vectors.
    scalar_vel_i = np.dot(unit_normal, vel_i)
    scalar_vel_j = np.dot(unit_normal, vel_j)
    scalar_tan_i = np.dot(unit_tangent, vel_i)

    # Convert the scalar normal and tangential velocities into vectors.
    vel_i = scalar_vel_j * unit_normal
    vel_j = scalar_vel_i * unit_normal
    tan_i = scalar_tan_i * unit_tangent

    # Finding the final velocity vectors by adding the normal and tangential components + friction.
    new_vel_i = (vel_i + tan_i) * friction
    new_vel_j = (vel_j + tan_i) * friction
    velX[i], velY[i] = new_vel_i[0], new_vel_i[1]
    velX[j], velY[j] = new_vel_j[0], new_vel_j[1]


def update(dt):
    global posX, posY, velX, velY, num_shapes

    collision_grid = [[[]
                       for _ in range(window.width // (radius * 2))]
                      for _ in range(window.height // (radius * 2))]

    for index, disk in enumerate(disks):
        disk.x = posX[index]
        disk.y = posY[index]

    # Updating position based on velocity.
    posX += velX * dt
    posY += velY * dt

    for index in range(len(disks)):
        x_grid = int(posX[index] // (radius * 2))
        y_grid = int(posY[index] // (radius * 2))

        if window.height // (radius * 2) > y_grid > -1 and window.width // (radius * 2) > x_grid > -1:
            collision_grid[y_grid][x_grid].append(index)

    for row_i in range(len(collision_grid) - 1):
        for col_j in range(len(collision_grid[row_i]) - 1):
            indices = []
            for element in collision_grid[row_i][col_j]:
                indices.append(element)
            for element in collision_grid[row_i][col_j + 1]:
                indices.append(element)
            for element in collision_grid[row_i + 1][col_j]:
                indices.append(element)
            for element in collision_grid[row_i + 1][col_j + 1]:
                indices.append(element)

            if len(indices) > 1:
                indices = np.array(indices)

                for i in range(len(indices)):
                    for j in range(i + 1, len(indices)):
                        disp = np.array([posX[indices[j]] - posX[indices[i]], posY[indices[j]] - posY[indices[i]]])
                        dist = np.sqrt((disp[0])**2 + (disp[1])**2)

                        if dist < (radius * 2):
                            # Finding overlap, unit normal vector and unit tangent vector.
                            overlap = dist - (radius * 2)
                            unit_normal = disp / (radius * 2)

                            # Handling collisions
                            collision_handler(indices[i], indices[j], unit_normal)

                            # Moving the disks in the unit_normal direction until they don't overlap anymore.
                            move(indices[i], overlap, unit_normal)
                            move(indices[j], overlap, -unit_normal)

    # Collisions with wall.
    for item in collision_grid[0]:
        for element in item:
            if posY[element] < radius:
                posY[element] = radius
                velY[element] *= momentum_loss
                velX[element] *= friction

    for item in collision_grid[len(collision_grid) - 1]:
        for element in item:
            if posY[element] > window.height - radius:
                posY[element] = window.height - radius
                velY[element] *= momentum_loss
                velX[element] *= friction

    for index in range(len(collision_grid)):
        for element in collision_grid[index][0]:
            if posX[element] < radius:
                posX[element] = radius
                velX[element] *= momentum_loss
                velY[element] *= friction

    for index in range(len(collision_grid)):
        for element in collision_grid[index][-1]:
            if posX[element] > window.width - radius:
                posX[element] = window.width - radius
                velX[element] *= momentum_loss
                velY[element] *= friction

    # Setting X vel under 0.0005 equal to 0, for performance reasons.
    velX[abs(velX) < 0.0005] = 0

    # Updating velocity due to gravity.
    velY -= gravity * dt



@window.event
def on_draw():
    window.clear()
    batch.draw()
    num_shapes.draw()
    if np.any(bitMap):
        event_handler()


clock.schedule_interval(update, 1/480)
app.run()
