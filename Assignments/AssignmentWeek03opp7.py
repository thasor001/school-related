from random import randint, choice

# pyglet imports:
from pyglet.window import Window
from pyglet.window import key
from pyglet.app import run
from pyglet.shapes import Line, Circle, Rectangle
from pyglet.graphics import Batch

# Human class that contains all the shapes of my figure.
# i drew a human :)
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


# Window class that contains the window.
class MyWindow(Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        # Variables used in the code:
        self.shapesCircle = []
        self.shapesLine = []

        self.batch = Batch()

        # The 4 different colors used in 7a)
        self.colors = [(0, 0, 255), (0, 255, 0), (255, 0, 0), (255, 255, 255)]

        self.size = (1080, 720)

        self.x = self.size[0]/2-25
        self.y = self.size[1]/2-10

        self.human = Human(self.x, self.y)

        self.assignment = 0

    # functions that are used to calculate: length, dot product and projections.
    def length(self, vecU):
        return (vecU[0] ** 2 + vecU[1] ** 2) ** 0.5

    def dot(self, vecU, vecV):
        return vecU[0] * vecV[0] + vecU[1] * vecV[1]

    def project(self, vecU, vecV):
        return [((self.dot(vecU, vecV) / (self.length(vecV)**2))*vecV[j]) for j in range(2)]

    # inbuilt function that keeps track of keyboard presses.
    def on_key_press(self, symbol, modifiers):
        # Space bar used to switch between 7a and 7b.
        if symbol == key.SPACE:
            self.assignment += 1

        # WASD used to move figure.
        if self.assignment % 2 != 0:
            if symbol == key.D:
                self.x += 10
            if symbol == key.A:
                self.x -= 10
            if symbol == key.W:
                self.y += 10
            if symbol == key.S:
                self.y -= 10

    # 7a)
    def draw0(self):
        self.batch.draw()

        # Lines collision with sides of the screen.
        for line in self.shapesLine:
            line[0].color = self.colors[1]
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

            # Movement for lines.
            line[0].x += line[1]
            line[0].y += line[2]
            line[0].x2 += line[1]
            line[0].y2 += line[2]

        # Circle collision with screen among other things:
        for index, (circle) in enumerate(self.shapesCircle):
            if circle[0].x + circle[0].radius < 0:
                circle[0].x = window.size[0] - circle[1]
            if circle[0].x - circle[0].radius > window.size[0]:
                circle[0].x = 0 + circle[1]

            if circle[0].y + circle[0].radius < 0:
                circle[0].y = window.size[1] - circle[2]
            if circle[0].y - circle[0].radius > window.size[1]:
                circle[0].y = 0 + circle[2]

            self.shapesCircle[index][0].color = self.colors[0]

            # Circle collision with other circles:
            for collision in self.shapesCircle:
                # Circle collision with lines:
                for lindex, (line) in enumerate(self.shapesLine):

                    # Vector between the two points in the line.
                    line_vec = [line[0].x2 - line[0].x,
                                line[0].y2 - line[0].y]

                    # Vector from line x, y and circle x, y.
                    circle_vec = [circle[0].x - line[0].x,
                                  circle[0].y - line[0].y]

                    # Variable used for length of line vector calculated using length function.
                    line_length = self.length(line_vec)
                    # Projection from circle vector onto line vector using projection function.
                    projection = self.project(circle_vec, line_vec)

                    # Finding the length from the projection to circle center using trigonometry k1^2+k2^2 = H^2.
                    # Solved it for the unknown K: k2 = H - k1, k1 = projection from circle vec onto line vec,
                    # H = circle vec, using this we find the unknown distance from line to circle.
                    linedistance = self.length([circle_vec[0] - projection[0], circle_vec[1] - projection[1]])

                    # First checks if this distance is less than the radius of the circle.
                    if linedistance <= circle[0].radius:
                        # Using the dot product to check if cos(circle_vec, line_vec) is within 90deg.
                        dot_product = self.dot(projection, line_vec)

                        # I could not get the code that was given in capquiz to work so, I made my own solution:
                        # the logic goes like this:
                        # The dot product is less than or equal to 0 "0 <= dot_product" means that cos is within,
                        # 0 - 90 deg or 270 - 360 deg witch gives positive cos values.
                        # Dot product is less than line length^2 "dot_product <= line_length ** 2" comes from,
                        # dot product (proj, proj) cant be longer that the line length,
                        # dot product proj^2 = |proj|^2 * cos (cos = 1). This ensures that the projection isn't longer,
                        # than what the line vector is.
                        if 0 <= dot_product <= line_length ** 2:
                            circle[0].color = self.colors[3]
                            self.shapesLine[lindex][0].color = self.colors[2]
                        else:
                            # This only activates if line length is less than circle radius and cos is inbetween,
                            # 90 - 270 deg, when cos is this we cant use projection anymore, then we just use,
                            # vec from the two different points in the line.
                            # If either of the two different vectors are less in length than circle radius,
                            # COLORS :)!
                            circle_vec2 = [circle[0].x - line[0].x2,
                                          circle[0].y - line[0].y2]
                            if (self.length(circle_vec) < circle[0].radius) \
                                    or (self.length(circle_vec2) < circle[0].radius):
                                circle[0].color = self.colors[3]
                                self.shapesLine[lindex][0].color = self.colors[2]

                    # Checks that the circle in the first loop is not the same as the second loop.
                    if (circle[0].x, circle[0].y) != (collision[0].x, collision[0].y):
                        # Distance between circles.
                        circledistance = ((circle[0].x - collision[0].x) ** 2 +
                                          (circle[0].y - collision[0].y) ** 2) ** 0.5

                        # If distance is less than both radius's COLOR :)!
                        if circledistance < circle[0].radius + collision[0].radius:
                            self.shapesCircle[index][0].color = self.colors[2]

            # Movement for the circles.
            circle[0].x += circle[1]
            circle[0].y += circle[2]

    # 7b)
    def draw1(self):
        # Draw Human class figure:
        self.human.batch.draw()

        # Always creates a new "human" with MyWindow's class x and y variables.
        # This way i can move the "human" figure with just moving 1 position.
        self.human = Human(self.x, self.y)

    def on_draw(self):
        self.clear()
        # Fetches window size, I know that I don't need to use this and I can just use window.size,
        # but found that out late and cant be bothered to change it :).
        self.size = list(self.get_size())
        # Switching between 7a and 7b.
        if self.assignment % 2 == 0:
            self.draw0()
        else:
            self.draw1()


if __name__ == "__main__":
    # Creates window with MyWindow class.
    window = MyWindow(width=1080, height=720, caption="AssignmentWeek03", resizable=True)

    # Creates 20 circles and 5 lines.
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
    # Start game loop :).
    run()
