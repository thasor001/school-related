from random import randint, choice

# pyglet imports:
import pyglet


class MyWindow(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.shapesCircle = []
        self.shapesLine = []
        self.batch1 = pyglet.graphics.Batch()
        self.batch2 = pyglet.graphics.Batch()

        self.size = (1080, 720)

        self.assignment = True

    def length(self, vecU):
        return (vecU[0] ** 2 + vecU[1] ** 2) ** 0.5

    def project(self, vecU, vecV, lengthV):
        proj = (vecU[0] * vecV[0] + vecU[1] * vecV[1]) / lengthV ** 2
        nx = vecV[0] * proj
        ny = vecV[1] * proj
        return [nx, ny]

    def dot(self, vecU, vecV):
        return vecU[0] * vecV[0] + vecU[1] * vecV[1]

    def on_key_press(self, symbol, modifiers):
        if symbol == pyglet.window.key.SPACE:
            window.assignment = False

    def on_key_release(self, symbol, modifiers):
        if symbol == pyglet.window.key.SPACE:
            window.assignment = True

    def draw0(self):
        window.batch1.draw()

        collisionMapCircle = []

        # Creating a collision map for circles.
        for shape in window.shapesCircle:
            collisionMapCircle.append([shape[0].x, shape[0].y, shape[0].radius])

        # Collision between screen and line.
        for line in window.shapesLine:
            line[0].color = (0, 255, 0)
            tempX = line[0].x
            tempX2 = line[0].x2
            tempY = line[0].y
            tempY2 = line[0].y2

            if (line[0].x < 0) and (line[0].x2 < 0):
                line[0].x = window.size[0] + abs(tempX2)
                line[0].x2 = window.size[0] + abs(tempX)

            if (line[0].x > window.size[0]) and (line[0].x2 > window.size[0]):
                line[0].x = window.size[0] - abs(tempX2)
                line[0].x2 = window.size[0] - abs(tempX)

            if (line[0].y < 0) and (line[0].y2 < 0):
                line[0].y = window.size[1] + abs(tempY2)
                line[0].y2 = window.size[1] + abs(tempY)

            if (line[0].y > window.size[1]) and (line[0].y2 > window.size[1]):
                line[0].y = window.size[1] - abs(tempY2)
                line[0].y2 = window.size[1] - abs(tempY)

            line[0].x += line[1]
            line[0].y += line[2]
            line[0].x2 += line[1]
            line[0].y2 += line[2]

        for index, (circle) in enumerate(window.shapesCircle):
            if circle[0].x + circle[0].radius < 0:
                circle[0].x = window.size[0] - circle[1]

            if circle[0].x - circle[0].radius > window.size[0]:
                circle[0].x = 0 + circle[1]

            if circle[0].y + circle[0].radius < 0:
                circle[0].y = window.size[1] - circle[2]

            if circle[0].y - circle[0].radius > window.size[1]:
                circle[0].y = 0 + circle[2]

            window.shapesCircle[index][0].color = (0, 0, 255)

            for cindex, (collision) in enumerate(collisionMapCircle):
                for line in window.shapesLine:

                    line_vec = [line[0].x2 - line[0].x,
                                line[0].y2 - line[0].y]

                    circle_vec = [circle[0].x - line[0].x,
                                  circle[0].y - line[0].y]

                    line_length = window.length(line_vec)
                    projection = window.project(circle_vec, line_vec, line_length)

                    linedistance = window.length([circle_vec[0] - projection[0], circle_vec[1] - projection[1]])

                    if linedistance <= circle[0].radius:
                        dot_product = window.dot(projection, line_vec)

                        if 0 <= dot_product <= line_length ** 2:
                            circle[0].color = (128, 0, 128)

                    circledistance = ((circle[0].x - collision[0]) ** 2 + (circle[0].y - collision[1]) ** 2) ** 0.5

                    if (circle[0].x, circle[0].y) != (collision[0], collision[1]):

                        if circledistance < circle[0].radius + collision[2]:
                            window.shapesCircle[index][0].color = (255, 0, 0)
                            window.shapesCircle[cindex][0].color = (255, 0, 0)

            circle[0].x += circle[1]
            circle[0].y += circle[2]

    def draw1(self):
        pass

    def on_draw(self):
        window.clear()
        window.size = list(window.get_size())
        if self.assignment:
            window.draw0()
        else:
            window.draw1()


if __name__ == "__main__":
    window = MyWindow(width=1080, height=720, caption="AssignmentWeek03", resizable=True)
    for i in range(20):
        radius = randint(15, 30)
        x = randint(0 + radius, window.size[0] - radius)
        y = randint(0 + radius, window.size[1] - radius)
        window.shapesCircle.append([pyglet.shapes.Circle(radius=radius,
                                                         color=(0, 0, 255),
                                                         x=x,
                                                         y=y,
                                                         batch=window.batch1),
                                    choice([-2, -1, 1, 2]),
                                    choice([-2, -1, 1, 2])])
    for i in range(10):
        x1 = (randint(50, window.size[0]))
        y1 = (randint(50, window.size[1]))
        x2 = x1 + choice([-1, 1]) * randint(40, 100)
        y2 = y1 + choice([-1, 1]) * randint(40, 100)
        window.shapesLine.append([pyglet.shapes.Line(x=x1,
                                                     y=y1,
                                                     x2=x2,
                                                     y2=y2,
                                                     color=(0, 255, 0),
                                                     batch=window.batch1),
                                  choice([-2, -1, 1, 2]),
                                  choice([-2, -1, 1, 2])])
    pyglet.app.run()