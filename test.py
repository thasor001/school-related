import pyglet

import random



class MyWindow(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.set_location(x=400, y=200)

        self.G = 9

        self.shapes = []
        self.batch = pyglet.graphics.Batch()


    def on_mouse_press(self, x, y, button, modifiers):
        if button == pyglet.window.mouse.LEFT:
            window.shapes.append([
                pyglet.shapes.Circle(x=x,
                                    y=y,
                                    radius=40,
                                    color=(255, 0, 0),
                                    batch=self.batch),
                                    1,
                                    1])


    def gravity(self):
        for window.item in window.shapes:
            window.item[1] += 1



    def on_draw(self):
        window.gravity()
        window.clear()
        window.batch.draw()



if __name__ == "__main__":
    window = MyWindow(width=1080, height=720, resizable=True, caption="test")
    pyglet.app.run()