import pyglet, random
from pyglet.window import mouse
'''
@author : Tharald Roland Sørensen
Resources:  https://www.youtube.com/playlist?list=PL1FgJUcJJ03s7kYUy40ydTA9gBnj_KDlK
            https://pyglet.readthedocs.io/en/latest/programming_guide/windowing.html
            https://www.youtube.com/playlist?list=PL42MzI01SYj7unM-kMN1nf70smlIsLDc0
'''

# Window size
sizeX = 1280
sizeY = 1280//2

# Draw window
window = pyglet.window.Window(caption="GGS", resizable=False, height=sizeY, width=sizeX)


@window.event
class MyWindow(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super(MyWindow, self).__init__(*args, **kwargs)

    def on_key_press(self, symbol, modifiers):
        if symbol == pyglet.window.key.A:
            print("You pressed A")


# Label to draw on screen
label = pyglet.text.Label("Hello world")

# Batch of shapes
buttons = pyglet.graphics.Batch()

# Shape Rectangle: batch: Buttons
square = pyglet.shapes.Rectangle(sizeX//2-200/2, sizeY//2-100/2, 200, 100, color=(random.randrange(0,255),255,255), batch=buttons)

# Get image
#image = pyglet.image.load("./AssignmentWeek1Pics/Dad.JPG")

# Draw image
#sprite = pyglet.sprite.Sprite(image, x=100, y=100)


@window.event
def on_draw():
    # Clears the window.
    window.clear()

    # Draws the label
    #label.draw()

    # Draws 100 squares on random places.
    #for i in range (100):
    #    draw_square(random.randrange(0, sizeX), random.randrange(0, sizeY), random.randrange(0,255))

    #sprite.draw()
    buttons.draw()


# Function that draws squares
def draw_square(x, y, c):
    shape = pyglet.shapes.Rectangle(x-50/2, y-50/2, 50, 50, color=(c, 0, 0))
    shape.draw()


# Starts the program.
pyglet.app.run()