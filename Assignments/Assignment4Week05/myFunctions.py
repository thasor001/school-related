def posUptade(shape, dt) -> None:
    shape.t += dt/shape.ts * shape.vel
    if shape.t > 1 or shape.t < 0:
        shape.vel *= -1


def quadBezier(obj, start, control, end) -> None:
    obj.x = start[0] * (1-obj.t)**2 + 2 * control[0] * obj.t * (1-obj.t) + end[0] * obj.t**2
    obj.y = start[1] * (1-obj.t)**2 + 2 * control[1] * obj.t * (1-obj.t) + end[1] * obj.t**2


def linearBezier(obj, start, end) -> None:
    obj.x = start[0] * (1-obj.t) + end[0] * obj.t
    obj.y = start[1] * (1-obj.t) + end[1] * obj.t
