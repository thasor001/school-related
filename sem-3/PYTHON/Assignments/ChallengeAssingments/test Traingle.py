from pyglet import *
from math import *
import numpy as np

window = window.Window(1000, 750)

triangle_batch = graphics.Batch()

class myCircle:
    def __init__(self, init_pos, radius):
        self.center = init_pos
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

    def rotate(self, angle):
        for i in range(self.numberTriangles):
            self.angles[i] += angle
            self.triangles[i].x2 = self.center[0] + self.radius * cos(self.angles[i])
            self.triangles[i].y2 = self.center[1] + self.radius * sin(self.angles[i])
            self.triangles[i].x3 = self.center[0] + self.radius * cos(self.angles[i]+pi/50)
            self.triangles[i].y3 = self.center[1] + self.radius * sin(self.angles[i]+pi/50)







circle = myCircle([window.width//2-155, window.height//2], 10)

circle2 = myCircle([window.width//2+155, window.height//2], 10)



def update(dt):
    global myShape, numberTriangles
    circle2.rotate(pi/100)


@window.event()
def on_draw():
    window.clear()
    triangle_batch.draw()


clock.schedule_interval(update, 1/60)
app.run()