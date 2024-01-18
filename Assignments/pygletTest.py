from pyglet.shapes import Circle, Line
from pyglet import window
from pyglet.window import key, mouse
from pyglet.app import run
from random import randint, choice

'''
@Author Tharald Roland Sørensen.


Menu:
M - Multiply circles by 10x, there can be a max of 100 circles before,
collisions with other circles are turned off due to performance,
maximum of 10000 circles again due to performance. Spawned circles sometimes,
spawn into each other and get stuck.

D - Deletes all circles except first one. collisional re turned on again.

R - Release controlled Circle, controlled circles are colored red and move,
towards the cursor.

Right Click - Control Circle, controlled circles are colored Red and move,
towards the cursor. Controlled circles Do not collide with anything.

Left Click - Click on two different x and y positions, creates a line between them.
'''

# Window size
wx, wy = 1280, 720

window = window.Window(wx, wy, caption='@Author Tharald Roland Sørensen')

shapes = []
lines = []
mousepos = [0, 0]
pos = [0, 0, 0, 0]

collisionMap = []

count = 0

collisions = True
spawn = False

shapes.append([Circle(200, 200, radius=50, color=(255, 0, 0)), 1, -1, True])


def motion(mx, my, shape):
    while abs(shape.x - mx) >= 1 and abs(shape.y - my) >= 1:
        distX, distY = mx - shape.x, my - shape.y
        ratio = min(1, 1 / max(abs(distX), abs(distY)))
        shape.x += distX * ratio/10
        shape.y += distY * ratio/10


@window.event
def on_mouse_press(x, y, button, modifiers):
    if button == mouse.RIGHT:
        index = 0
        for shape, vx, vy, control in shapes:
            if (x, y) in shape:
                print("Shape Captured")
                shapes[index][3] = True
                shape.color = (255, 0, 0)
            index += 1
    if button == mouse.LEFT:
        global count
        count += 1
        if count == 1:
            pos[count-1] = x
            pos[count] = y
        elif count == 2:
            pos[count] = x
            pos[count+1] = y
            drawLine(pos[0], pos[1], pos[2], pos[3])
            count = 0


def drawLine(x1, y1, x2, y2):
    lines.append(Line(x1, y1, x2, y2, color=(0, 255, 0)))


@window.event
def on_key_press(symbol, modifiers):
    if symbol == key.R:
        print("Shapes Released")
        for index, (shape, vx, vy, control) in enumerate(shapes):
            if shapes[index][3]:
                shapes[index][3] = False
                shape.color = (0, 0, 255)
    if symbol == key.M:
        global spawn
        global collisions
        if len(shapes) < 10000:
            print("10X shapes")
            spawn = True
        else:
            print("Too many shapes.")
    if symbol == key.D:
        if len(shapes) == 1:
            print("Cant delete last circle.")
        for i in range(len(shapes)-1):
            shapes.pop(-1)
        collisions = True


def circleSpawn(map,n):
    global collisions
    while len(shapes) < n:
        radius = randint(20, 30)
        rx = randint(0 + radius, wx - radius)
        print(rx)
        ry = randint(0 + radius, wy - radius)
        rc = randint(50, 255)
        vx, vy = choice([2, -2]), choice([2, -2])
        if len(shapes) >= 101:
            shapes.append([Circle(rx, ry, radius, color=(0, 0, rc)), vx, vy, False])
            collisions = False
        else:
            canSpawn = True
            for colX, colY, cradius, cvx, cvy in map:
                distance = ((rx - colX) ** 2 + (ry - colY) ** 2) ** 0.5
                if distance <= radius + cradius:
                    canSpawn = False
            if canSpawn:
                shapes.append([Circle(rx, ry, radius, color=(0, 0, rc)), vx, vy, False])



@window.event
def on_mouse_motion(x, y, dx, dy):
    mousepos[0] = x
    mousepos[1] = y


@window.event
def on_draw():
    window.clear()
    global spawn
    for line in lines:
        line.draw()
    global collisionMap
    for shape in shapes:
        collisionMap.append([shape[0].x, shape[0].y, shape[0].radius, shape[1], shape[2]])
    if spawn:
        print(len(shapes)* 10)
        circleSpawn(collisionMap, len(shapes) * 10)
        print(len(shapes), " shapes")
        spawn = False
    for index, (shape, vx, vy, control) in enumerate(shapes):
        if not shapes[index][3]:
            if shape.x >= wx-shape.radius or shape.x <= 0+shape.radius:
                vx *= -1
            elif shape.y >= wy-shape.radius or shape.y <= 0+shape.radius:
                vy *= -1
            shapes[index][1] = vx
            shapes[index][2] = vy
        else:
            motion(mousepos[0], mousepos[1], shape)
        if collisions:
            for cindex, (colX, colY, radius, cvx, cvy) in enumerate(collisionMap):
                if (shape.x, shape.y) != (colX, colY):
                    distance = ((shape.x - colX) ** 2 + (shape.y - colY) ** 2) ** 0.5
                    if distance <= shape.radius + radius:
                        if not shapes[cindex][3]:
                            vx, cvx = cvx, vx
                            vy, cvy = cvy, vy
        shape.x += (1*vx)
        shape.y += (1*vy)
        shapes[index][1] = vx
        shapes[index][2] = vy
        shape.draw()

    collisionMap = []

run()