import pyglet
from pyglet.window import *
from pyglet.graphics import *
from pyglet.app import *

class MyWindow(Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def update(self, dt):
        print(dt)
        self.clear()

        window.fps_display.draw()

if __name__ == "__main__":
    window = MyWindow(width=1080, height=720, caption="Assignment3", resizable=True)

    window.fps_display = FPSDisplay(window=window)

    pyglet.clock.schedule_interval(window.update, 1.0/60.0)

run()
