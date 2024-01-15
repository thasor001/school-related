import pyglet

windowX, windowY = 1280, 720


window = pyglet.window.Window(windowX, windowY, caption='PygletTest')

shapes = []

shapes.append(pyglet.shapes.Circle(200, 200, 50, color=(0, 255, 255)))
shapes.append(pyglet.shapes.Circle(500, 500, 100, color=(0, 0, 255)))



@window.event
def on_mouse_drag(mx, my, dx, dy, buttons, modifiers):
    for shape in shapes:
        if (mx, my) in shape:
            motionX = abs(abs(shape.x) - abs(mx))
            motionY = abs(abs(shape.y) - abs(my))
            print("Motion X: ", motionX, "Motion Y: ", motionY)
            shape.x = mx
            shape.y = my


@window.event
def on_draw():
    window.clear()
    for shape in shapes:
        vx, vy = 1, 1
        if shape.x >= windowX-shape.radius or shape.x <= 0-shape.radius:
            vx *= -1
        elif shape.y >= windowY-shape.radius or shape.y <= 0-shape.radius:
            vy *= -1
        shape.x += 1 * vx
        shape.y += 1 * vy
        shape.draw()


pyglet.app.run()