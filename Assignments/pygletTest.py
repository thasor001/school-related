import pyglet, time, random

windowX, windowY = 1280, 720

window = pyglet.window.Window(windowX, windowY, caption='PygletTest')

shapes = []

godMode = False

shapes.append([pyglet.shapes.Circle(200, 200, radius=100, color=(255, 0, 0)), 1, 1])
shapes.append([pyglet.shapes.Circle(100, 100, radius=50, color=(0, 255, 255)), 1, 1])


def motion(mx, my, shape):
    while abs(shape.x - mx) >= 1 and abs(shape.y - my) >= 1:
        distX, distY = mx - shape.x, my - shape.y
        ratio = min(1, 1 / max(abs(distX), abs(distY)))
        shape.x += distX * ratio
        shape.y += distY * ratio
        print(abs(shape.x - mx), abs(shape.y - my))



@window.event
def on_mouse_drag(mx, my, dx, dy, buttons, modifiers):
    for shape, vx, vy in shapes:
        if buttons == pyglet.window.mouse.RIGHT:
            if (mx, my) in shape:
                motion(mx, my, shape)
                print(godMode)


@window.event
def on_draw():
    window.clear()
    index = 0
    for shape, vx, vy in shapes:
        if shape.x >= windowX-shape.radius or shape.x <= 0+shape.radius:
            vx *= -1
        elif shape.y >= windowY-shape.radius or shape.y <= 0+shape.radius:
            vy *= -1
        shape.x += (1 * vx)
        shape.y += (1 * vy)
        shape.draw()
        shapes[index][1] = vx
        shapes[index][2] = vy
        index += 1


pyglet.app.run()