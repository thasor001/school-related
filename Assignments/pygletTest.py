from pyglet.shapes import *
from pyglet.window import *
from pyglet.app import *
from pyglet.graphics import *
from random import *

'''
@Author Tharald Roland Sørensen.

Menu:
M - Multiply circles by 10x, there can be a max of 100 circles before,
collisions with other circles are turned off due to performance,
maximum of 10000 circles again due to performance. Spawned circles sometimes,
spawn into each other and get stuck.

D - Deletes all circles except first one and assignment shapes. collisional re-turned on again.

R - Release controlled Circle, controlled circles are colored red and move,
towards the cursor.

H - Draw assignment shapes.

Right Click - Control Circle, controlled circles are colored Red and move,
towards the cursor. Controlled circles Do not collide with anything.

Left Click - Click on two different x and y positions, creates a line between them.
'''


# Initialize window-instance
class MainWindow(Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        # # Creates a batch that is used to quickly draw all lines and assignment shapes.
        self.batch = Batch()
        self.batch2 = Batch()

        # Fetching the fullscreen window size.
        self.windowsize = list(self.get_size())

        # Putting window size into variables used to map the edges of the screen.
        self.wx, self.wy = self.windowsize[0], self.windowsize[1]

        #
        # List of the different shapes.
        self.shapes = []
        self.Lines = []
        self.shapesForAssignment = []

        # Mouse position [x,y] shows where the mouse position is at all times through the inbuilt on_mouse_motion function.
        self.mousepos = [0, 0]

        # List that saves the two last positions that the mouse has left-clicked, used to draw lines inbetween them.
        self.pos = [0, 0, 0, 0]

        # A list that is used to map all the positions of shapes, used to check for collisions.
        self.collisionMap = []

        # Counter that keeps track on how many times the user has left-clicked, used to tell the program when to draw,
        # a line between the two stored positions in the "pos" list.
        self.count = 0

        # collisions activates and deactivates collisions,
        # spawn used to tell the program to spawn more and when it cant spawn more shapes.
        # window.assignmentShapes used to tell the program that the assignment shapes should be drawn.
        self.collisions = True
        self.spawn = False
        self.assignmentShapes = False

        # Creates the first shape, the first shape starts off ass shapes[0][3] = True, which indicates that
        # it is being controlled by the mouse.
        # The shapes list contains a lists of [shape, velocity X, velocity Y, Controlled]
        self.shapes.append([Circle(200, 200, radius=50, color=(255, 0, 0)), 1, 1, True])

    # Motion function for the mouse.
    def motion(self, mx, my, shape):
        # continues to run until the distance between the shapes x, y and the mouse x, y coordinate are less than 1.
        while abs(shape.x - mx) >= 1 and abs(shape.y - my) >= 1:
            distX, distY = mx - shape.x, my - shape.y
            ratio = min(1, 1 / max(abs(distX), abs(distY)))
            shape.x += distX * ratio / 15
            shape.y += distY * ratio / 15

    # Inbuilt on_mouse_press function. used to check if user is pressing right or left,
    # if left; capture shape if mouse x, y in shape x, y + radius
    def on_mouse_press(self, x, y, button, modifiers):
        if button == mouse.RIGHT:
            for index, (shape, vx, vy, control) in enumerate(window.shapes):
                if (x, y) in shape:
                    print("Shape Captured")
                    window.shapes[index][3] = True
                    shape.color = (255, 0, 0)
        if button == mouse.LEFT:
            window.count += 1
            if window.count == 1:
                window.pos[window.count - 1] = x
                window.pos[window.count] = y
            elif window.count == 2:
                window.pos[window.count] = x
                window.pos[window.count + 1] = y
                window.drawLine(window.pos[0],
                                window.pos[1],
                                window.pos[2],
                                window.pos[3])
                window.count = 0

    # function that takes in the pos list coordinates and draws a line inbetween them.
    def drawLine(self, x1, y1, x2, y2):
        window.Lines.append(Line(x1, y1, x2, y2, color=(0, 255, 0), batch=window.batch))

    # Inbuilt function that checks the key presses, used to check if key = R, M or D,
    # R; releases the shapes that the user has captured, M; Multiplies current amount of shapes by 10x,
    # D; deletes all current shapes except the first one.
    # H; draw assignment shapes.
    def on_key_press(self, symbol, modifiers):
        if symbol == key.R:
            print("Shapes Released")
            for index, (shape, vx, vy, control) in enumerate(window.shapes):
                if window.shapes[index][3]:
                    window.shapes[index][3] = False
                    shape.color = (0, 0, 255)
        if symbol == key.M:
            if len(window.shapes) < 10000:
                print("10X shapes")
                window.spawn = True
            else:
                print("Too many shapes.")
        if symbol == key.D:
            if len(window.shapes) == 1:
                print("Cant delete last circle.")
            for i in range(len(window.shapes) - 1):
                window.shapes.pop(-1)
            window.collisions = True
            window.assignmentShapes = False

        if symbol == key.H:
            window.shapesForAssignment.append(Circle(
                x=300,
                y=200,
                radius=100,
                color=(50, 225, 30),
                batch=window.batch2)
            )

            window.shapesForAssignment.append(Rectangle(
                x=400,
                y=100,
                width=100,
                height=200,
                color=(55, 55, 255),
                batch=window.batch2)
            )

            window.shapesForAssignment.append(Line(
                x=200,
                y=200,
                x2=100,
                y2=400,
                width=19,
                batch=window.batch2)
            )

            window.shapesForAssignment.append(
                Star(
                    x=900,
                    y=500,
                    outer_radius=65,
                    inner_radius=40,
                    num_spikes=12,
                    color=(255, 255, 0),
                    batch=window.batch2)
            )

            window.shapesForAssignment.append(
                Triangle(x=100,
                         y=200,
                         x2=100,
                         y2=40,
                         x3=414,
                         y3=27,
                         color=(55, 15, 255),
                         batch=window.batch2)
            )

            window.shapesForAssignment.append(Arc(
                x=200,
                y=200,
                radius=100,
                color=(15, 55, 155),
                batch=window.batch2)
            )

            window.shapesForAssignment.append(Ellipse(
                x=700,
                y=900,
                a=100,
                b=400,
                color=(255, 55, 55),
                batch=window.batch2)
            )

            window.shapesForAssignment.append(Sector(
                x=800,
                y=400, radius=100,
                segments=400,
                color=(255, 255, 255),
                batch=window.batch2)
            )

            window.assignmentShapes = True

    # Function used to map out the valid spawns for a new circle,
    # Makes it so that the circles do not spawn inside each other.
    def circleSpawn(self, shapelist, n):
        global collisions
        while len(window.shapes) < n:
            radius = randint(15, 25)
            rx = randint(0 + radius, window.wx - radius)
            ry = randint(0 + radius, window.wy - radius)
            rr, rg, rb = randint(0, 255), randint(0, 255), randint(0, 255)
            vx, vy = choice([2, -2]), choice([2, -2])
            if len(window.shapes) >= 101:
                window.shapes.append([Circle(rx, ry, radius, color=(rr, rg, rb)), vx, vy, False])
                collisions = False
            else:
                canSpawn = True
                for index, (shape, svx, svy, control) in enumerate(shapelist):
                    distance = ((rx - shape.x) ** 2 + (ry - shape.y) ** 2) ** 0.5
                    if distance <= 10 + radius + shape.radius:
                        canSpawn = False
                        break
                if canSpawn:
                    window.shapes.append([Circle(rx, ry, radius, color=(rr, rg, rb)), vx, vy, False])

    # Inbuilt function that checks where the mouse is, used to send current pos into mousepos list.
    def on_mouse_motion(self, x, y, dx, dy):
        window.mousepos[0] = x
        window.mousepos[1] = y

    # Inbuild function that runs all the time
    def on_draw(self):
        window.clear()
        window.batch.draw()
        if window.assignmentShapes:
            window.batch2.draw()
        # Fills the collisionMap list with all the positions of the shapes.
        for shape in window.shapes:
            window.collisionMap.append([shape[0].x, shape[0].y, shape[0].radius, shape[1], shape[2]])
        # Creates 10x shapes using circleSpawn function.
        if window.spawn:
            window.circleSpawn(window.shapes, len(window.shapes) * 10)
            print(len(window.shapes), " shapes")
            window.spawn = False
        # controls all movement and collisions
        for index, (shape, vx, vy, control) in enumerate(window.shapes):
            if not window.shapes[index][3]:
                if shape.x >= window.wx - shape.radius or shape.x <= 0 + shape.radius:
                    vx *= -1
                elif shape.y >= window.wy - shape.radius or shape.y <= 0 + shape.radius:
                    vy *= -1
                window.shapes[index][1] = vx
                window.shapes[index][2] = vy
            else:
                window.motion(window.mousepos[0], window.mousepos[1], shape)
            if window.collisions:
                for cindex, (colX, colY, radius, cvx, cvy) in enumerate(window.collisionMap):
                    if (shape.x, shape.y) != (colX, colY):
                        distance = ((shape.x - colX) ** 2 + (shape.y - colY) ** 2) ** 0.5
                        if distance <= shape.radius + radius:
                            if cindex < len(window.shapes) and not window.shapes[cindex][3]:
                                vx, cvx = cvx, vx
                                vy, cvy = cvy, vy
            if not window.shapes[index][3]:
                shape.x += vx
                shape.y += vy
                window.shapes[index][1] = vx
                window.shapes[index][2] = vy
            shape.draw()


if __name__ == '__main__':
    # Window properties
    window = MainWindow(caption='@Author Tharald Roland Sørensen', fullscreen=True)
    run()
