from pyglet import *
from myFunctions import *


class Circle(shapes.Circle):
    t, ts, vel = 0, 1, 1

    def __init__(self, x, y, r):
        super().__init__(x, y, r)
        self.x, self.y, self.radius = x, y, r
        self.batch = window.batch
        self.color = (255, 0, 255)

    @classmethod
    def updateTime(cls, dt):
        for shape in window.items:
            posUptade(shape, dt)
        for shape in window.cube:
            posUptade(shape, dt)


class MyWindow(window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.batch = graphics.Batch()
        self.items, self.cube = [], []
        self.timer = 0

    def update(self, dt):
        for obj in self.cube:
            quadBezier(obj, [window.width, window.height - 100], [window.width, 0], [20, 250])
            if obj.vel == -1:
                self.cube.pop(0)

        self.timer += 1
        if self.timer * dt >= 1 / 5:
            window.cube.append(Circle(window.width, window.height - 100, 10)); window.cube[-1].ts = 2
            self.timer = 0

        if (window.items and window.items[0].vel == -1) or len(window.items) < 1:
            window.items.insert(0, Circle(20, window.height-30, 20)); window.items[0].color = (255, 0, 0)
            if window.items and len(window.items) > 1: self.items.pop(1)

        linearBezier(window.items[0], [20, window.height - 30], [230, window.height - 30])

        Circle.updateTime(dt)

    def on_draw(self) -> None:
        self.clear()
        self.batch.draw()


if __name__ == "__main__":
    window = MyWindow(height=500, width=500, caption="Bezier Curve @Author Tharald")
    clock.schedule_interval(window.update, 1 / 60)

    app.run()
