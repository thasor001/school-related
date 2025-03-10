from pyglet import *
from math import *
from MyFunctions import *
from pyglet.window import mouse, key

triangle_batch = graphics.Batch()


def createCircle(pos, obj):
    direction = 1
    if pos[2][0] - pos[0][0] < 0:
        direction = -1
    obj.circles.append(myCircle(pos, radius=35, direction=direction))

class myCircle:
    t = 0
    tc = 0
    color_direction = 1
    ts = False
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
        self.start_Colors = []
        self.numberTriangles = 100
        self.count = 0
        self.controlled = False

        for i in range(self.numberTriangles):
            self.angles.append(2*pi*i/self.numberTriangles)
            self.start_Colors.append([(i + 100), 0, (i + 100)])
            self.triangles.append(
                shapes.Triangle(self.center[0], self.center[1],
                                self.center[0] + self.radius * cos(2 * pi * i / self.numberTriangles),
                                self.center[1] + self.radius * sin(2 * pi * i / self.numberTriangles),
                                self.center[0] + self.radius * cos(2 * pi * (i + 1) / self.numberTriangles),
                                self.center[1] + self.radius * sin(2 * pi * (i + 1) / self.numberTriangles),
                                batch=triangle_batch, color=self.start_Colors[i])
            )

    def move(self, x, y):
        self.center = [x, y]
        for i in range(self.numberTriangles):
            self.triangles[i].x = self.center[0]
            self.triangles[i].y = self.center[1]
            self.triangles[i].x2 = self.center[0] + self.radius * cos(self.angles[i])
            self.triangles[i].y2 = self.center[1] + self.radius * sin(self.angles[i])
            self.triangles[i].x3 = self.center[0] + self.radius * cos(self.angles[i] + pi / 50)
            self.triangles[i].y3 = self.center[1] + self.radius * sin(self.angles[i] + pi / 50)

    def rotate(self, angle):
        for i in range(self.numberTriangles):
            self.angles[i] += angle*self.direction
            self.triangles[i].x2 = self.center[0] + self.radius * cos(self.angles[i])
            self.triangles[i].y2 = self.center[1] + self.radius * sin(self.angles[i])
            self.triangles[i].x3 = self.center[0] + self.radius * cos((self.angles[i] + pi / 50))
            self.triangles[i].y3 = self.center[1] + self.radius * sin((self.angles[i] + pi / 50))

    def colorRotation(self):
        quadBezierColor(self)

    @classmethod
    def updateTime(cls, dt):
        for shape in window.circles:
            if shape.controlled:
                followMouse(shape, window.mouse_pos)
            else:
                posUptade(shape, dt)
                quadBezier(shape)
            if shape.count >= 1:
                myCircle.colorRotation(shape)
                shape.tc += dt/2 * shape.color_direction
                if shape.tc > 1:
                    shape.tc = 1
                    shape.color_direction *= -1
                elif shape.tc < 0:
                    shape.tc = 0
                    shape.color_direction *= -1
                if shape.count == 2:
                    shape.ts = True
                elif shape.count > 2:
                    shape.count = 0
                    shape.ts = False



class MyWindow(window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.batch = graphics.Batch()
        self.circles = []
        self.temp = []
        self.counter = 0
        self.tri_pos = []
        self.mouse_pos = []


    def on_mouse_press(self, x, y, button, modifiers):
        if button == mouse.LEFT:
            self.tri_pos.append([x, y])
            self.temp.append(shapes.Circle(x=x, y=y, radius=5,
                                           color=(15*self.counter*2, 230//(1+self.counter*95), 25*(self.counter*6)),
                                           batch=self.batch))
            self.counter += 1
            if self.counter == 3:
                createCircle(self.tri_pos, self)
                self.temp.clear()
                self.tri_pos.clear()
                self.counter = 0

        if button == mouse.RIGHT:
            cur_pos = [x, y]
            for i in range(len(self.circles)):
                vec = [self.circles[i].center[0] - cur_pos[0], self.circles[i].center[1] - cur_pos[1]]
                dist = sqrt(vec[0]**2 + vec[1]**2)
                if dist < self.circles[i].radius:
                    self.circles[i].count += 1

    def on_key_press(self, symbol, modifiers):
        if symbol == key.D:
            for shape in self.circles:
                vec = [shape.center[0] - self.mouse_pos[0], shape.center[1] - self.mouse_pos[1]]
                dist = sqrt(vec[0]**2 + vec[1]**2)
                if dist < shape.radius:
                    self.circles.remove(shape)
                    print("Shape Removed")
        if symbol == key.C:
            for shape in self.circles:
                vec = [shape.center[0] - self.mouse_pos[0], shape.center[1] - self.mouse_pos[1]]
                dist = sqrt(vec[0] ** 2 + vec[1] ** 2)
                if dist < shape.radius:
                    shape.controlled = True
        if symbol == key.K:
            for shape in self.circles:
                shape.controlled = True
        if symbol == key.A:
            for shape in self.circles:
                shape.count = 1
        if symbol == key.S:
            for shape in self.circles:
                shape.ts = True

    def on_key_release(self, symbol, modifiers):
        if symbol == key.C:
            for shape in self.circles:
                if shape.controlled:
                    shape.controlled = False
                    shape.t = 1 / 2
                    shape.control = [shape.center[0], shape.center[1]]
        if symbol == key.K:
            for shape in self.circles:
                shape.controlled = False
                shape.t = 1 / 2
                shape.control = [shape.center[0], shape.center[1]]
        if symbol == key.A:
            for shape in self.circles:
                shape.count = 0
        if symbol == key.S:
            for shape in self.circles:
                shape.ts = False

    def on_mouse_motion(self, x, y, dx, dy):
        self.mouse_pos = [x, y]


    # Update function.
    def update(self, dt):
        for shape in window.circles:
            myCircle.rotate(shape, pi*dt)
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
