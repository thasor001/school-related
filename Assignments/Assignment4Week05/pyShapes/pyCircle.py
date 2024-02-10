

class Circle(shapes.Circle):
    def __init__(self, x, y, radius):
        super().__init__(x, y, radius)
        self.radius = radius
        self.x = x
        self.y = y
        self.batch = window.batch
        self.color = (0, 0, 255, 255)

    @classmethod
    def new_pos(cls, x, y):
        pass