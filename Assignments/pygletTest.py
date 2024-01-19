from pyglet.shapes import Circle, Line, Rectangle, Star
from pyglet import window
from pyglet.window import key, mouse
from pyglet.app import run
from pyglet.graphics import Batch
from random import randint, choice

'''
@Author Tharald Roland Sørensen.

The shapes sometimes "clump together" and can then escape the screen, this happens due to the way i handle,
collisions, fixing it would take a lot of time so im just leaving it as it is.

recourses used:
https://pyglet.readthedocs.io/en/latest/index.html

Menu:
M - Multiply circles by 10x, there can be a max of 100 circles before,
collisions with other circles are turned off due to performance,
maximum of 10000 circles again due to performance. Spawned circles sometimes,
spawn into each other and get stuck.

D - Deletes all circles except first one. collisional re turned on again.

R - Release controlled Circle, controlled circles are colored red and move,
towards the cursor.

H - Draw assignment shapes.

Right Click - Control Circle, controlled circles are colored Red and move,
towards the cursor. Controlled circles Do not collide with anything.

Left Click - Click on two different x and y positions, creates a line between them.
'''


# Creates the window
window = window.Window(caption='@Author Tharald Roland Sørensen', fullscreen=True)

# Fetching the fullscreen window size.
size = list(window.get_size())

# Putting window size into variables used to map the edges of the screen.
wx, wy = size[0], size[1]

# Creates a batch that is used to quickly draw all lines and assignment shapes.
batch = Batch()
batch2 = Batch()

# List of the different shapes.
shapes = []
Lines = []
shapesForAssignment = []

# Mouse position [x,y] shows where the mouse position is at all times through the inbuilt on_mouse_motion function.
mousepos = [0, 0]

# List that saves the two last positions that the mouse has left-clicked, used to draw lines inbetween them.
pos = [0, 0, 0, 0]

# A list that is used to map all the positions of shapes, used to check for collisions.
collisionMap = []

# Counter that keeps track on how many times the user has left-clicked, used to tell the program when to draw,
# a line between the two stored positions in the "pos" list.
count = 0

# collisions activates and deactivates collisions,
# spawn used to tell the program to spawn more and when it cant spawn more shapes.
# assignmentShapes used to tell the program that the assignment shapes should be drawn.
collisions = True
spawn = False
assignmentShapes = False

# Creates the first shape, the first shape starts off ass shapes[0][3] = True, which indicates that
# it is being controlled by the mouse.
shapes.append([Circle(200, 200, radius=50, color=(255, 0, 0)), 1, 1, True])

# Motion function for the mouse.
def motion(mx, my, shape):
    # continues to run until the distance between the shapes x, y and the mouse x, y coordinate are less than 1.
    while abs(shape.x - mx) >= 1 and abs(shape.y - my) >= 1:
        distX, distY = mx - shape.x, my - shape.y
        ratio = min(1, 1 / max(abs(distX), abs(distY)))
        shape.x += distX * ratio/15
        shape.y += distY * ratio/15


# Inbuilt on_mouse_press function. used to check if user is pressing right or left,
# if left; capture shape if mouse x, y in shape x, y + radius
@window.event
def on_mouse_press(x, y, button, modifiers):
    if button == mouse.RIGHT:
        for index, (shape, vx, vy, control) in enumerate(shapes):
            if (x, y) in shape:
                print("Shape Captured")
                shapes[index][3] = True
                shape.color = (255, 0, 0)
    if button == mouse.LEFT:
        global count
        count += 1
        if count == 1:
            pos[count-1] = x
            pos[count] = y
        elif count == 2:
            pos[count] = x
            pos[count+1] = y
            drawLine(pos[0], pos[1], pos[2], pos[3])
            count = 0


# function that takes in the pos list coordinates and draws a line inbetween them.
def drawLine(x1, y1, x2, y2):
    Lines.append(Line(x1, y1, x2, y2, color=(0, 255, 0), batch=batch))


# Inbuilt function that checks the key presses, used to check if key = R, M or D,
# R; releases the shapes that the user has captured, M; Multiplies current amount of shapes by 10x,
# D; deletes all current shapes except the first one.
# H; draw assignment shapes.
@window.event
def on_key_press(symbol, modifiers):
    if symbol == key.R:
        print("Shapes Released")
        for index, (shape, vx, vy, control) in enumerate(shapes):
            if shapes[index][3]:
                shapes[index][3] = False
                shape.color = (0, 0, 255)
    if symbol == key.M:
        global spawn
        global collisions
        global assignmentShapes
        if len(shapes) < 10000:
            print("10X shapes")
            spawn = True
        else:
            print("Too many shapes.")
    if symbol == key.D:
        if len(shapes) == 1:
            print("Cant delete last circle.")
        for i in range(len(shapes)-1):
            shapes.pop(-1)
        collisions = True
        assignmentShapes = False
    if symbol == key.H:
        shapesForAssignment.append(Circle(700, 150, 100, color=(50, 225, 30), batch=batch2))
        shapesForAssignment.append(Rectangle(200, 200, 200, 200, color=(55, 55, 255), batch=batch2))
        shapesForAssignment.append(Line(100, 100, 100, 200, width=19, batch=batch2))
        shapesForAssignment.append(Star(800, 400, 60, 40, num_spikes=20, color=(255, 255, 0), batch=batch2))
        assignmentShapes = True


# Function used to map out the valid spawns for a new circle,
# Makes it so that the circles do not spawn inside each other.
def circleSpawn(shapelist, n):
    global collisions
    while len(shapes) < n:
        radius = randint(15, 25)
        rx = randint(0 + radius, wx - radius)
        ry = randint(0 + radius, wy - radius)
        rr, rg, rb = randint(0, 255), randint(0, 255), randint(0, 255)
        vx, vy = choice([2, -2]), choice([2, -2])
        if len(shapes) >= 101:
            shapes.append([Circle(rx, ry, radius, color=(rr, rg, rb)), vx, vy, False])
            collisions = False
        else:
            canSpawn = True
            for index, (shape, svx, svy, control) in enumerate(shapelist):
                distance = ((rx - shape.x) ** 2 + (ry - shape.y) ** 2) ** 0.5
                if distance <= 10 + radius + shape.radius:
                    canSpawn = False
                    break
            if canSpawn:
                shapes.append([Circle(rx, ry, radius, color=(rr, rg, rb)), vx, vy, False])


# Inbuilt function that checks where the mouse is, used to send current pos into mousepos list.
@window.event
def on_mouse_motion(x, y, dx, dy):
    mousepos[0] = x
    mousepos[1] = y


# Inbuild function that runs all the time
@window.event
def on_draw():
    window.clear()
    global spawn
    global collisionMap
    global assignmentShapes
    collisionMap = []
    batch.draw()
    if assignmentShapes:
        batch2.draw()
    # Fills the collisionMap list with all the positions of the shapes.
    for shape in shapes:
        collisionMap.append([shape[0].x, shape[0].y, shape[0].radius, shape[1], shape[2]])
    # Creates 10x shapes using circleSpawn function.
    if spawn:
        circleSpawn(shapes, len(shapes) * 10)
        print(len(shapes), " shapes")
        spawn = False
    # controls all movement and collisions
    for index, (shape, vx, vy, control) in enumerate(shapes):
        if not shapes[index][3]:
            if shape.x >= wx-shape.radius or shape.x <= 0+shape.radius:
                vx *= -1
            elif shape.y >= wy-shape.radius or shape.y <= 0+shape.radius:
                vy *= -1
            shapes[index][1] = vx
            shapes[index][2] = vy
        else:
            motion(mousepos[0], mousepos[1], shape)
        if collisions:
            for cindex, (colX, colY, radius, cvx, cvy) in enumerate(collisionMap):
                if (shape.x, shape.y) != (colX, colY):
                    distance = ((shape.x - colX) ** 2 + (shape.y - colY) ** 2) ** 0.5
                    if distance <= 5 + shape.radius + radius:
                        if not shapes[cindex][3]:
                            vx, cvx = cvx, vx
                            vy, cvy = cvy, vy
        if not shapes[index][3]:
            shape.x += (1*vx)
            shape.y += (1*vy)
            shapes[index][1] = vx
            shapes[index][2] = vy
        shape.draw()

# runs the code.
run()