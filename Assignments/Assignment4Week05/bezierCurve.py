from pyglet import *


class Circle(shapes.Circle):
    def __init__(self, x, y, radius):
        super().__init__(x, y, radius)
        self.radius = radius
        self.x = x
        self.y = y
        self.batch = window.batch
        self.color = (0, 0, 255, 255)

    @classmethod
    def new_pos(cls, x, y):
        pass



class Square(shapes.Rectangle):
    def __init__(self, x, y, height, width):
        super().__init__(x, y, height, width)
        self.height = height
        self.width = width
        self.x = x
        self.y = y
        self.color = (0, 255, 0, 255)
        self.batch = window.batch


class MyWindow(window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.batch = graphics.Batch()
        self.time = 0
        self.items = []

    def on_draw(self):
        self.clear()
        self.batch.draw()

if __name__ == "__main__":
    window = MyWindow(height=500, width=500, caption="Bezier Curve")
    window.items.append(Circle(x=100, y=100, radius=25))
    window.items.append(Square(x=350, y=350, height=50, width=50))

app.run()