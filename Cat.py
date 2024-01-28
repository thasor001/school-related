import pyglet


class Human:
    def __init__(self, x, y):

        self.x = x
        self.y = y

        self.batch = pyglet.graphics.Batch()

        self.rectangle = pyglet.shapes.Rectangle(x=self.x,
                                                 y=self.y,
                                                 width=50,
                                                 height=100,
                                                 color=(255, 255, 255),
                                                 batch=self.batch)


class MyWindow(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.human = Human(self.width // 2 - 25, self.height // 2 - 50)


    def on_key_press(self, symbol, modifiers):
        if symbol == pyglet.window.key.D:
            self.human = Human(200, 200)

    def on_draw(self):
        self.clear()

        self.human.batch.draw()

if __name__ == "__main__":
    window = MyWindow(width=1080, height=720, caption="Cat Test", resizable=True)

    pyglet.app.run()