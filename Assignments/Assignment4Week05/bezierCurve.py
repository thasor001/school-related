from pyglet import *
from myFunctions import *


class Circle(shapes.Circle):
    t, ts, vel, s, t3 = 0, 1, 1, False, False

    def __init__(self, x, y, r):
        super().__init__(x, y, r)
        self.x, self.y, self.radius = x, y, r
        self.batch = window.batch
        self.color, self.start, self.end = (255, 0, 255), [], []

    @classmethod
    def updateTime(cls, dt):
        for shape in window.items + window.cube:
            posUptade(shape, dt)


class MyWindow(window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.batch = graphics.Batch()
        self.items, self.cube, self.timer = [], [], 0

    def update(self, dt):
        for obj in self.cube:
            quadBezier(obj, [self.width, self.height - 100], [self.width, 0], [20, 150])
            if obj.vel == -1:
                self.cube.pop(0)

        self.timer += 1
        if self.timer * dt >= 1 / 5:
            self.cube.append(Circle(self.width, self.height - 100, 10))
            self.cube[-1].ts, self.timer = 2, 0

        if self.items[0].vel == -1:
            self.items.pop(0)
            self.items.insert(0, Circle(20, self.height-30, 20))
            setUp(self.items[0], (255, 0, 0), 5, [20, self.height - 30], [230, self.height - 30])

        for i in range(len(self.items)):
            linearBezier(self.items[i], self.items[i].start, self.items[i].end)

        Circle.updateTime(dt)

    def on_draw(self) -> None:
        self.clear()
        self.batch.draw()


if __name__ == "__main__":
    window = MyWindow(height=500, width=500, caption="Bezier Curve @Author Tharald")
    clock.schedule_interval(window.update, 1 / 60)

    window.items.append(Circle(20, window.height - 30, 20))
    setUp(window.items[0], (255, 0, 0), 5, [20, window.height - 30], [230, window.height - 30])

    window.items.append(Circle(20, window.height-80, 20))
    setUp(window.items[1], (255, 255, 0), 2, [20, window.height - 80], [230, window.height - 80])

    window.items.append(Circle(20, window.height-130, 20)); window.items[2].s = True
    setUp(window.items[2], (0, 255, 0), 2, [20, window.height - 130], [230, window.height - 130])

    window.items.append(Circle(20, window.height-180, 20)); window.items[3].t3, window.items[3].s = True, True
    setUp(window.items[3], (0, 0, 255), 5, [20, window.height - 180], [230, window.height - 180])

    window.items.append(Circle(55, window.height-300, 50)); window.items[4].s = True
    setUp(window.items[4], (255, 0, 0), 2, [0], [50])

    window.items.append(Circle(255, window.height-300, 50)); window.items[5].s = True
    setUp(window.items[5], (0, 255, 0), 2, [1, 254, 1, 50], [254, 254, 1, 25])

    window.items.append(Circle(155, window.height-300, 50))
    setUp(window.items[6], (0, 255, 0), 2, [1, 254, 1], [254, 1, 1])
    app.run()
