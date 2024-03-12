import pyglet

sizeX, sizeY = 1280, 720
items = []


class RenderWindow(pyglet.window.Window):
    def __init__(self):
        super().__init__(sizeX, sizeY, "@Author Tharald Roland Sørensen")
        for i in range (300):
            self.item = pyglet.shapes.Circle(500, 200, 25, color=(0, 200, 200))

    def on_mouse_drag(self, x, y, dx, dy, buttons, modifiers):
        if buttons == pyglet.window.mouse.LEFT:
            print("Left mouse button pressed")


    # Pyglet inbuilt function that runs whenever a frame is requested.
    def on_draw(self):
        self.clear()
        self.item.draw()


renderer = RenderWindow()
pyglet.app.run()