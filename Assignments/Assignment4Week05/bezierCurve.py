from pyglet import *


def posUptade(shape, dt):
    shape.t += dt * shape.vel
    if not shape.ret and shape.t > 1:
        shape.t = 0
    else:
        if shape.t > 1 or shape.t < 0:
            shape.vel *= -1
            shape.t += dt * shape.vel


class Circle(shapes.Circle):
    t = 0
    vel = 1
    ret = False

    def __init__(self, x, y, radius):
        super().__init__(x, y, radius)
        self.radius = radius
        self.x = x
        self.y = y
        self.batch = window.batch
        self.color = (0, 0, 255, 255)

    @classmethod
    def updateTime(cls, dt):
        for shape in window.items:
            if isinstance(shape, list):
                for obj in shape:
                    posUptade(obj, dt)
            else:
                posUptade(shape, dt)



class MyWindow(window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.batch = graphics.Batch()
        self.items = []
        self.cube = []

    def cubeBezier(self, start, control, end, t) -> None:
        pass

    def update(self, dt) -> None:
        for obj in self.cube:
            self.cubeBezier([window.width, window.height-100],
                            [window.width, 0],
                            [20, 350], obj.t)

        Circle.updateTime(dt)

    def on_draw(self) -> None:
        self.clear()
        self.batch.draw()


if __name__ == "__main__":
    window = MyWindow(height=500, width=500, caption="Bezier Curve")
    window.items.append(Circle(window.width, window.height-100, 25))

    clock.schedule_interval(window.update, 1/60.)

    window.items.append(window.cube)
    app.run()
