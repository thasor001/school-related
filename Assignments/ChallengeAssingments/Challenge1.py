from pyglet import *
from math import *
from MyFunctions import *


triangle_batch = graphics.Batch()

def quadBezier(obj):
    myCircle.move(
        obj,
        (obj.start[0] * (1 - obj.t) ** 2 + 2 * obj.control[0] * obj.t * (1 - obj.t) + obj.end[0] * obj.t ** 2),
        (obj.start[1] * (1 - obj.t) ** 2 + 2 * obj.control[1] * obj.t * (1 - obj.t) + obj.end[1] * obj.t ** 2)
    )

def createCircle(pos, obj):
    direction = 1
    if pos[2][0] - pos[0][0] < 0:
        direction = -1
    obj.circles.append(myCircle(pos, radius=25, direction=direction))

class myCircle:
    t = 0
    vel = 1/2
    def __init__(self, init_pos, radius, direction):
        self.center = init_pos[0]
        self.start = init_pos[0]
        self.control = init_pos[1]
        self.end = init_pos[2]
        self.direction = direction
        self.radius = radius
        self.angles = []
        self.triangles = []
        self.numberTriangles = 100

        for i in range(self.numberTriangles):
            self.angles.append(2*pi*i/self.numberTriangles)
            self.triangles.append(
                shapes.Triangle(self.center[0], self.center[1],
                                self.center[0] + self.radius * cos(2 * pi * i / self.numberTriangles),
                                self.center[1] + self.radius * sin(2 * pi * i / self.numberTriangles),
                                self.center[0] + self.radius * cos(2 * pi * (i + 1) / self.numberTriangles),
                                self.center[1] + self.radius * sin(2 * pi * (i + 1) / self.numberTriangles),
                                batch=triangle_batch, color=(i + 100, 0, i + 100))
            )

    def move(self, x, y):
        self.center = [x, y]
        print(self.center)
        for i in range(self.numberTriangles):
            self.triangles[i].x = self.center[0]
            self.triangles[i].y = self.center[1]
            self.triangles[i].x2 = self.center[0] + self.radius * cos(self.angles[i])
            self.triangles[i].y2 = self.center[1] + self.radius * sin(self.angles[i])
            self.triangles[i].x3 = self.center[0] + self.radius * cos(self.angles[i] + pi / 50)
            self.triangles[i].y3 = self.center[1] + self.radius * sin(self.angles[i] + pi / 50)

    def rotate(self, angle):
        for i in range(self.numberTriangles):
            self.angles[i] += angle
            self.triangles[i].x2 = self.center[0] + self.radius * cos(self.angles[i])
            self.triangles[i].y2 = self.center[1] + self.radius * sin(self.angles[i])
            self.triangles[i].x3 = self.center[0] + self.radius * cos(self.angles[i]+pi/50)
            self.triangles[i].y3 = self.center[1] + self.radius * sin(self.angles[i]+pi/50)

    @classmethod
    def updateTime(cls, dt):
        for shape in window.circles:
            posUptade(shape, dt)
            quadBezier(shape)

class MyWindow(window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.batch = graphics.Batch()
        self.circles = []
        self.temp = []
        self.counter = 0
        self.tri_pos = []


    def on_mouse_press(self, x, y, button, modifiers):
        self.tri_pos.append((x, y))
        self.temp.append(shapes.Circle(x=x, y=y, radius=5,
                                       color=(15*self.counter*2, 230//(1+self.counter*95), 25*(self.counter*6)),
                                       batch=self.batch))
        self.counter += 1
        if self.counter == 3:
            createCircle(self.tri_pos, self)
            self.temp.clear()
            self.tri_pos.clear()
            self.counter = 0

    # Update function.
    def update(self, dt):
        pass

    def on_draw(self):
        self.clear()
        triangle_batch.draw()
        self.batch.draw()


if __name__ == "__main__":
    window = MyWindow(height=750, width=1000, caption="challenge @Author Tharald")
    clock.schedule_interval(window.update, 1 / 60)
    clock.schedule_interval(myCircle.updateTime, 1 / 60)

    app.run()
