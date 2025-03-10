import pyglet


class Human:
    def __init__(self, x, y):

        self.parentX = x
        self.parentY = y

        self.batch = pyglet.graphics.Batch()
        self.body = pyglet.shapes.Rectangle(x=self.parentX,
                                            y=self.parentY,
                                            width=50,
                                            height=100,
                                            color=(200, 200, 200),
                                            batch=self.batch)
        self.head = pyglet.shapes.Circle(x=self.parentX+25,
                                         y=self.parentY+125,
                                         radius=25,
                                         color=(255, 255, 255),
                                         batch=self.batch)
        self.rightArm = pyglet.shapes.Rectangle(x=self.parentX+self.body.width,
                                                y=self.parentY+self.body.height,
                                                width=10,
                                                height=-40,
                                                color=(255, 255, 255),
                                                batch=self.batch)
        self.leftArm = pyglet.shapes.Rectangle(x=self.parentX-10,
                                               y=self.parentY + self.body.height,
                                               width=10,
                                               height=-40,
                                               color=(255, 255, 255),
                                               batch=self.batch)
        self.rightLeg = pyglet.shapes.Rectangle(x=self.parentX+self.body.width-20,
                                                y=self.parentY,
                                                width=20,
                                                height=-45,
                                                color=(255, 255, 255),
                                                batch=self.batch)
        self.leftLeg = pyglet.shapes.Rectangle(x=self.parentX,
                                               y=self.parentY,
                                               width=20,
                                               height=-45,
                                               color=(255, 255, 255),
                                               batch=self.batch)
        self.rightForehand = pyglet.shapes.Rectangle(x=self.rightArm.x,
                                                     y=self.rightArm.y+self.rightArm.height,
                                                     width=10,
                                                     height=-35,
                                                     color=(255, 255, 255),
                                                     batch=self.batch)
        self.leftForehand = pyglet.shapes.Rectangle(x=self.leftArm.x,
                                                    y=self.leftArm.y + self.leftArm.height,
                                                    width=10,
                                                    height=-35,
                                                    color=(255, 255, 255),
                                                    batch=self.batch)

        self.rightChin = pyglet.shapes.Rectangle(x=self.rightLeg.x,
                                                 y=self.rightLeg.y+self.rightLeg.height,
                                                 width=20,
                                                 height=-40,
                                                 color=(255, 255, 255),
                                                 batch=self.batch)
        self.leftChin = pyglet.shapes.Rectangle(x=self.leftLeg.x,
                                                y=self.leftLeg.y+self.leftLeg.height,
                                                width=20,
                                                height=-40,
                                                color=(255, 255, 255),
                                                batch=self.batch)
        self.rightHand = pyglet.shapes.Circle(x=self.rightForehand.x+5,
                                              y=self.rightForehand.y+self.rightForehand.height,
                                              radius=10,
                                              color=(255, 255, 255),
                                              batch=self.batch)
        self.leftHand = pyglet.shapes.Circle(x=self.leftForehand.x + 5,
                                             y=self.leftForehand.y + self.leftForehand.height,
                                             radius=10,
                                             color=(255, 255, 255),
                                             batch=self.batch)
        self.rightFoot = pyglet.shapes.Rectangle(x=self.rightChin.x,
                                                 y=self.rightChin.y+self.rightChin.height,
                                                 width=30,
                                                 height=10,
                                                 color=(0, 255, 255),
                                                 batch=self.batch)
        self.leftFoot = pyglet.shapes.Rectangle(x=self.leftChin.x-10,
                                                y=self.leftChin.y + self.leftChin.height,
                                                width=30,
                                                height=10,
                                                color=(0, 255, 255),
                                                batch=self.batch)
        self.hatBrim = pyglet.shapes.Rectangle(x=self.head.x-30,
                                               y=self.head.y+10,
                                               width=60,
                                               height=10,
                                               color=(100, 100, 100),
                                               batch=self.batch)
        self.hatTop = pyglet.shapes.Rectangle(x=self.hatBrim.x+self.hatBrim.width/4,
                                              y=self.hatBrim.y+self.hatBrim.height,
                                              width=30,
                                              height=20,
                                              color=(100, 100, 100),
                                              batch=self.batch)



class MyWindow(pyglet.window.Window):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.human = Human(self.width // 2 - 25, self.height // 2 - 50)


    def on_key_press(self, symbol, modifiers):
        if symbol == pyglet.window.key.D:
            self.human = Human(200, 200)

    def on_draw(self):
        self.clear()

        self.human.batch.draw()

if __name__ == "__main__":
    window = MyWindow(width=1080, height=720, caption="Cat Test", resizable=True)

    pyglet.app.run()