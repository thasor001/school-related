from random import randint, choice

# pyglet imports:
from pyglet.window import Window
from pyglet.window import key
from pyglet.app import run
from pyglet.shapes import Line, Circle, Rectangle
from pyglet.graphics import Batch

class Human:
    def __init__(self, x, y):

        self.parentX = x
        self.parentY = y

        self.batch = Batch()
        self.body = Rectangle(x=self.parentX,
                              y=self.parentY,
                              width=50,
                              height=100,
                              color=(200, 200, 200),
                              batch=self.batch)
        self.head = Circle(x=self.parentX+25,
                           y=self.parentY+125,
                           radius=25,
                           color=(255, 255, 255),
                           batch=self.batch)
        self.rightArm = Rectangle(x=self.parentX+self.body.width,
                                  y=self.parentY+self.body.height,
                                  width=10,
                                  height=-40,
                                  color=(200, 200, 200),
                                  batch=self.batch)
        self.leftArm = Rectangle(x=self.parentX-10,
                                 y=self.parentY + self.body.height,
                                 width=10,
                                 height=-40,
                                 color=(200, 200, 200),
                                 batch=self.batch)
        self.rightLeg = Rectangle(x=self.parentX+self.body.width-20,
                                  y=self.parentY,
                                  width=20,
                                  height=-45,
                                  color=(165, 42, 42),
                                  batch=self.batch)
        self.leftLeg = Rectangle(x=self.parentX,
                                 y=self.parentY,
                                 width=20,
                                 height=-45,
                                 color=(165, 42, 42),
                                 batch=self.batch)
        self.rightForehand = Rectangle(x=self.rightArm.x,
                                       y=self.rightArm.y+self.rightArm.height,
                                       width=10,
                                       height=-35,
                                       color=(255, 255, 255),
                                       batch=self.batch)
        self.leftForehand = Rectangle(x=self.leftArm.x,
                                      y=self.leftArm.y + self.leftArm.height,
                                      width=10,
                                      height=-35,
                                      color=(255, 255, 255),
                                      batch=self.batch)
        self.rightChin = Rectangle(x=self.rightLeg.x,
                                   y=self.rightLeg.y+self.rightLeg.height,
                                   width=20,
                                   height=-40,
                                   color=(255, 255, 255),
                                   batch=self.batch)
        self.leftChin = Rectangle(x=self.leftLeg.x,
                                  y=self.leftLeg.y+self.leftLeg.height,
                                  width=20,
                                  height=-40,
                                  color=(255, 255, 255),
                                  batch=self.batch)
        self.rightHand = Circle(x=self.rightForehand.x+5,
                                y=self.rightForehand.y+self.rightForehand.height,
                                radius=10,
                                color=(255, 255, 255),
                                batch=self.batch)
        self.leftHand = Circle(x=self.leftForehand.x + 5,
                               y=self.leftForehand.y + self.leftForehand.height,
                               radius=10,
                               color=(255, 255, 255),
                               batch=self.batch)
        self.rightFoot = Rectangle(x=self.rightChin.x,
                                   y=self.rightChin.y+self.rightChin.height,
                                   width=30,
                                   height=10,
                                   color=(0, 255, 255),
                                   batch=self.batch)
        self.leftFoot = Rectangle(x=self.leftChin.x-10,
                                  y=self.leftChin.y + self.leftChin.height,
                                  width=30,
                                  height=10,
                                  color=(0, 255, 255),
                                  batch=self.batch)
        self.hatBrim = Rectangle(x=self.head.x-30,
                                 y=self.head.y+10,
                                 width=60,
                                 height=10,
                                 color=(100, 100, 100),
                                 batch=self.batch)
        self.hatTop = Rectangle(x=self.hatBrim.x+self.hatBrim.width/4,
                                y=self.hatBrim.y+self.hatBrim.height,
                                width=30,
                                height=20,
                                color=(100, 100, 100),
                                batch=self.batch)


class MyWindow(Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.shapesCircle = []
        self.shapesLine = []

        self.batch = Batch()

        self.size = (1080, 720)

        self.x = self.size[0]/2-25
        self.y = self.size[1]/2-10

        self.human = Human(self.x, self.y)

        self.assignment = 0

        self.G = 5
        self.terminalVelocity = -10

    def length(self, vecU):
        return (vecU[0] ** 2 + vecU[1] ** 2) ** 0.5

    def dot(self, vecU, vecV):
        return vecU[0] * vecV[0] + vecU[1] * vecV[1]

    def project(self, vecU, vecV):
        return [((self.dot(vecU, vecV) / (self.length(vecV)**2))*vecV[j]) for j in range(2)]

    def on_key_press(self, symbol, modifiers):
        if symbol == key.SPACE:
            self.assignment += 1
        if self.assignment % 2 != 0:
            if symbol == key.D:
                self.x += 10
            if symbol == key.A:
                self.x -= 10
            if symbol == key.W:
                self.y += 10
            if symbol == key.S:
                self.y -= 10

    def draw0(self):
        self.batch.draw()

        for line in self.shapesLine:
            line[0].color = (0, 255, 0)
            tempX = line[0].x
            tempX2 = line[0].x2
            tempY = line[0].y
            tempY2 = line[0].y2

            if (line[0].x < 0) and (line[0].x2 < 0):
                line[0].x = self.size[0] + abs(tempX)
                line[0].x2 = self.size[0] + abs(tempX2)
            if (line[0].x > self.size[0]) and (line[0].x2 > self.size[0]):
                line[0].x = self.size[0] - abs(tempX2)
                line[0].x2 = self.size[0] - abs(tempX)

            if (line[0].y < 0) and (line[0].y2 < 0):
                line[0].y = self.size[1] + abs(tempY)
                line[0].y2 = self.size[1] + abs(tempY2)

            if (line[0].y > self.size[1]) and (line[0].y2 > self.size[1]):
                line[0].y = self.size[1] - abs(tempY2)
                line[0].y2 = self.size[1] - abs(tempY)

            line[0].x += line[1]
            line[0].y += line[2]
            line[0].x2 += line[1]
            line[0].y2 += line[2]

        for index, (circle) in enumerate(self.shapesCircle):
            if circle[0].x + circle[0].radius < 0:
                circle[0].x = window.size[0] - circle[1]

            if circle[0].x - circle[0].radius > window.size[0]:
                circle[0].x = 0 + circle[1]

            if circle[0].y + circle[0].radius < 0:
                circle[0].y = window.size[1] - circle[2]

            if circle[0].y - circle[0].radius > window.size[1]:
                circle[0].y = 0 + circle[2]

            self.shapesCircle[index][0].color = (0, 0, 255)

            for collision in self.shapesCircle:
                for lindex, (line) in enumerate(self.shapesLine):

                    line_vec = [line[0].x2 - line[0].x,
                                line[0].y2 - line[0].y]

                    circle_vec = [circle[0].x - line[0].x,
                                  circle[0].y - line[0].y]

                    line_length = self.length(line_vec)
                    projection = self.project(circle_vec, line_vec)

                    linedistance = self.length([circle_vec[0] - projection[0], circle_vec[1] - projection[1]])

                    if linedistance <= circle[0].radius:
                        dot_product = self.dot(projection, line_vec)

                        if 0 <= dot_product <= line_length ** 2:
                            circle[0].color = (255, 0, 255)
                            self.shapesLine[lindex][0].color = (128, 128, 128)
                        else:
                            circle_vec2 = [circle[0].x - line[0].x2,
                                          circle[0].y - line[0].y2]
                            if (self.length(circle_vec) < circle[0].radius) \
                                    or (self.length(circle_vec2) < circle[0].radius):
                                circle[0].color = (255, 0, 255)
                                self.shapesLine[lindex][0].color = (128, 128, 128)


                    circledistance = ((circle[0].x - collision[0].x) ** 2 + (circle[0].y - collision[0].y) ** 2) ** 0.5

                    if (circle[0].x, circle[0].y) != (collision[0].x, collision[0].y):

                        if circledistance < circle[0].radius + collision[0].radius:
                            self.shapesCircle[index][0].color = (255, 0, 0)

            circle[0].x += circle[1]
            circle[0].y += circle[2]

    def draw1(self):
        self.human.batch.draw()
        self.human = Human(self.x, self.y)

    def on_draw(self):
        self.clear()
        self.size = list(self.get_size())
        if self.assignment % 2 == 0:
            self.draw0()
        else:
            self.draw1()


if __name__ == "__main__":
    window = MyWindow(width=1080, height=720, caption="AssignmentWeek03", resizable=True)
    for i in range(20):
        radius = randint(15, 30)
        x = randint(0 + radius, window.size[0] - radius)
        y = randint(0 + radius, window.size[1] - radius)
        window.shapesCircle.append([Circle(radius=radius,
                                           color=(0, 0, 255),
                                           x=x,
                                           y=y,
                                           batch=window.batch),
                                    choice([-2, -1, 1, 2]),
                                    choice([-2, -1, 1, 2])])
    for i in range(5):
        x1 = (randint(50, window.size[0]))
        y1 = (randint(50, window.size[1]))
        x2 = x1 + choice([-1, 1]) * randint(40, 100)
        y2 = y1 + choice([-1, 1]) * randint(40, 100)
        window.shapesLine.append([Line(x=x1,
                                       y=y1,
                                       x2=x2,
                                       y2=y2,
                                       color=(0, 255, 0),
                                       batch=window.batch),
                                  choice([-2, -1, 1, 2]),
                                  choice([-2, -1, 1, 2])])
    run()
