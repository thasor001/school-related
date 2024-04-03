from pyglet import *
import numpy as np
from time import time

window = window.Window(width=1000, height=750, caption="Task2 Author@Tharald")
batch = graphics.Batch()



start_time = time()


end_time = time()

print("Test took", end_time - start_time, " Seconds")



def update(dt):
    pass


@window.event
def on_draw():
    window.clear()
    batch.draw()


clock.schedule_interval(update, 1/60)
app.run()
