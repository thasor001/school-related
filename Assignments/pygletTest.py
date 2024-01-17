import pyglet
from random import randint, choice

wx, wy = 1280, 720

window = pyglet.window.Window(wx, wy, caption='@Author Tharald Roland Sørensen')

shapes = []
lines = []
mouse = [0, 0]
pos = [0, 0, 0, 0]

count = 0

collisions = True

shapes.append([pyglet.shapes.Circle(200, 200, radius=50, color=(255, 0, 0)), 0, 0, True])


def motion(mx, my, shape):
    while abs(shape.x - mx) >= 1 and abs(shape.y - my) >= 1:
        distX, distY = mx - shape.x, my - shape.y
        ratio = min(1, 1 / max(abs(distX), abs(distY)))
        shape.x += distX * ratio/10
        shape.y += distY * ratio/10


@window.event
def on_mouse_press(x, y, button, modifiers):
    if button == pyglet.window.mouse.RIGHT:
        index = 0
        for shape, vx, vy, control in shapes:
            if (x, y) in shape:
                print("Shape Captured")
                shapes[index][3] = True
                shape.color = (255, 0, 0)
            index += 1
    if button == pyglet.window.mouse.LEFT:
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
    lines.append(pyglet.shapes.Line(x1, y1, x2, y2, color=(0, 255, 0)))


@window.event
def on_key_press(symbol, modifiers):
    if symbol == pyglet.window.key.R:
        print("Shapes Released")
        index = 0
        for shape, vx, vy, control in shapes:
            if shapes[index][3]:
                shapes[index][3] = False
                shape.color = (0, 0, 255)
            index += 1
    if symbol == pyglet.window.key.M:
        if len(shapes) <= 1000:
            global collisions
            print("10X shapes!!!")
            for i in range((len(shapes))*10-len(shapes)):
                radius = randint(10, 50)
                rx = randint(0+radius, wx-radius)
                ry = randint(0+radius, wy-radius)
                rc = randint(50, 255)
                vx, vy = choice([2, -2]), choice([2, -2])
                shapes.append([pyglet.shapes.Circle(rx, ry, radius=radius, color=(0, 0, rc)), vx, vy, False])
            if len(shapes) == 1000:
                print("Collisions turned off for 1000 shapes.")
                collisions = False
        else:
            print("Too many shapes.")
    if symbol == pyglet.window.key.D:
        if len(shapes) > 1:
            for i in range(len(shapes)):
                print("a")
        else:
            print("Cant divide only 1 shape")

@window.event
def on_mouse_motion(x, y, dx, dy):
    mouse[0] = x
    mouse[1] = y

@window.event
def on_draw():
    window.clear()
    index = 0
    for line in lines:
        line.draw()
    # Bounce off walls.
    for shape, vx, vy, control in shapes:
        if not shapes[index][3]:
            if shape.x >= wx-shape.radius or shape.x <= 0+shape.radius:
                vx *= -1
            elif shape.y >= wy-shape.radius or shape.y <= 0+shape.radius:
                vy *= -1
            shape.x += (1 * vx)
            shape.y += (1 * vy)
            shapes[index][1] = vx
            shapes[index][2] = vy
        shape.draw()
        if shapes[index][3]:
            motion(mouse[0], mouse[1], shape)
        index += 1



pyglet.app.run()