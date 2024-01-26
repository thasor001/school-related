import pyglet


class MyWindow(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.set_location(x=400, y=200)

        self.size = (720, 500)

        self.G = 9
        self.terminalVelocity = 10

        self.shapes = []
        self.batch = pyglet.graphics.Batch()

    def gravity(self):
        for item in window.shapes:
            item[2] -= 1/window.G
            if item[2] > window.terminalVelocity:
                item[2] = window.terminalVelocity

    def on_draw(self):
        window.size = list(window.get_size())
        window.gravity()
        window.clear()
        window.batch.draw()
        for shape in window.shapes:
            if shape[0].y <= shape[0].radius:
                shape[0].y = shape[0].radius
                shape[2] *= 1/2
                shape[4] *= -1
            shape[0].y += shape[2] * shape[4]

if __name__ == "__main__":
    window = MyWindow(width=720, height=500, resizable=True, caption="test")
    window.shapes.append([pyglet.shapes.Circle(x=200,
                                               y=450,
                                               radius=25,
                                               color=(0, 0, 255),
                                               batch=window.batch),
                          1, 1, 1, -1])
    pyglet.app.run()