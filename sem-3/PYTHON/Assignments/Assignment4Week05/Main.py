from pyglet import *
from myFunctions import *


# Cirlce class.
class Circle(shapes.Circle):
    # Values used (Messy :)) to tell program what to do with circles
    t, ts, vel, s, t3 = 0, 1, 1, False, False

    def __init__(self, x, y, r):
        super().__init__(x, y, r)
        self.x, self.y, self.radius = x, y, r
        self.batch = window.batch
        self.color, self.start, self.end = (255, 0, 255), [], []

    # Class method, updates alle circle class's time with parameter dt
    @classmethod
    def updateTime(cls, dt):
        for shape in window.items + window.cube:
            posUptade(shape, dt)


# Window Class
class MyWindow(window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.batch = graphics.Batch()
        self.items, self.cube, self.timer = [], [], 0

    # Update function.
    def update(self, dt):
        for obj in self.cube:
            # Moves shapes in cube list in a quadratic Beziercurve -> see MyFunctions file.
            quadBezier(obj, [self.width, self.height - 100],
                       [self.width, 0], [20, 150])
            # I have made it so that when a gets to its end they all change direction, but if these circles,
            # change direction I delete the element.
            if obj.vel == -1:
                self.cube.pop(0)

        # Timer that spawn's new circles for the quad-bez, once every 1 / 5 seconds so that there will be 10 circles,
        # on screen.
        self.timer += 1
        if self.timer * dt >= 1 / 5:
            self.cube.append(Circle(self.width, self.height - 100, 10))
            self.cube[-1].ts, self.timer = 2, 0

        # This is for the red circle, since this and the quad-bez are the only ones that do not change direction,
        # I just delete this one as well and just create a new one at the start of window.items list.
        if self.items[0].vel == -1:
            self.items.pop(0)
            self.items.insert(0, Circle(20, self.height-30, 20))
            setUp(self.items[0], (255, 0, 0), 5, [20, self.height - 30], [230, self.height - 30])

        # Moves all circles in window.items with a linear Beziercurve -> see MyFunctions file.
        for i in range(len(self.items)):
            linearBezier(self.items[i], self.items[i].start, self.items[i].end)

        # Class function for Circles -> see Circle class.
        Circle.updateTime(dt)

    def on_draw(self) -> None:
        self.clear()
        self.batch.draw()


if __name__ == "__main__":
    # initiate the window and a clock for update function.
    window = MyWindow(height=500, width=500, caption="Bezier Curve @Author Tharald")
    clock.schedule_interval(window.update, 1 / 60)

    # initiates circles in window.items list.
    window.items.append(Circle(20, window.height - 30, 20))
    # Setup function that takes in circle color, time for on full cycle, start and end position -> see MyFunctions file.
    setUp(window.items[0], (255, 0, 0), 5, [20, window.height - 30], [230, window.height - 30])

    window.items.append(Circle(20, window.height-80, 20))
    setUp(window.items[1], (255, 255, 0), 2, [20, window.height - 80], [230, window.height - 80])

    # if circle has .s = True, means that it moves in a smoothstep -> see myFunctions file (ps).
    window.items.append(Circle(20, window.height-130, 20)); window.items[2].s = True
    setUp(window.items[2], (0, 255, 0), 2, [20, window.height - 130], [230, window.height - 130])

    # if circle has .s, t3 = True, True, means that it is the blue circle with the janky movement -> see -- || -- (ps).
    window.items.append(Circle(20, window.height-180, 20)); window.items[3].t3, window.items[3].s = True, True
    setUp(window.items[3], (0, 0, 255), 5, [20, window.height - 180], [230, window.height - 180])

    window.items.append(Circle(55, window.height-300, 50)); window.items[4].s = True
    setUp(window.items[4], (255, 0, 0), 2, [0], [50])

    # Different circles have different amount of variables in start and end 2 means normal start end, 3 means color,
    # 4 means color and radius needs to change and length 1 only radius -> see MyFunctions file (linearBezier).
    window.items.append(Circle(255, window.height-300, 50)); window.items[5].s = True
    setUp(window.items[5], (0, 255, 0), 2, [0, 255, 0, 50], [255, 255, 0, 25])

    window.items.append(Circle(155, window.height-300, 50))
    setUp(window.items[6], (0, 255, 0), 2, [0, 255, 0], [255, 0, 0])
    app.run()
