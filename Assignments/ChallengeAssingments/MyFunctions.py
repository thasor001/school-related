

def posUptade(shape, dt):
    shape.t += dt * shape.vel
    if shape.t > 1:
        shape.t = 1
        shape.vel *= -1
    elif shape.t < 0:
        shape.t = 0
        shape.vel *= -1


