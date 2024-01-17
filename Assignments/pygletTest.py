import pyglet, random

windowX, windowY = 1280, 720

window = pyglet.window.Window(windowX, windowY, caption='@Author Tharald Roland Sørensen')

fps = 5

shapes = []
mouse = [0, 0]

shapes.append([pyglet.shapes.Circle(200, 200, radius=100, color=(0, 0, 255)), 1, 1, False])
shapes.append([pyglet.shapes.Circle(500, 200, radius=50, color=(0, 0, 255)), -1, 1, False])


def update(dt):
    print("frame rage = ", fps)


pyglet.clock.schedule_interval(update, 1.0 / fps)


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
                shapes[index][3] = True
                shape.color = (255, 0, 0)
            index += 1


@window.event
def on_key_press(symbol, modifiers):
    if symbol == pyglet.window.key.D:
        index = 0
        for shape, vx, vy, control in shapes:
            if shapes[index][3] == True:
                shapes[index][3] = False
                shape.color = (0, 0, 255)
            index += 1

@window.event
def on_mouse_motion(x, y, dx, dy):
    mouse[0] = x
    mouse[1] = y

@window.event
def on_draw():
    window.clear()
    index = 0
    # Bounce off walls.
    for shape, vx, vy, control in shapes:
        if not shapes[index][3]:
            if shape.x >= windowX-shape.radius or shape.x <= 0+shape.radius:
                vx *= -1
            elif shape.y >= windowY-shape.radius or shape.y <= 0+shape.radius:
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