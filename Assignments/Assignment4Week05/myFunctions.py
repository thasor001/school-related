def posUptade(shape, dt) -> None:
    shape.t += dt/shape.ts * shape.vel
    if shape.t > 1 or shape.t < 0:
        shape.vel *= -1

def quadBezier(obj, start, control, end) -> None:
    obj.x = start[0] * (1-obj.t)**2 + 2 * control[0] * obj.t * (1-obj.t) + end[0] * obj.t**2
    obj.y = start[1] * (1-obj.t)**2 + 2 * control[1] * obj.t * (1-obj.t) + end[1] * obj.t**2

def linearBezier(obj, start, end):
    if len(start) == 2 and len(end) == 2:
        obj.x, obj.y = (start[0]*(1-ps(obj))+end[0]*ps(obj), start[1]*(1-ps(obj))+end[1]*ps(obj))
        return
    elif len(start) > 2 and len(end) > 2:
        obj.color = [int((1-obj.t)*start[0]+obj.t*end[0]),
                     int((1-obj.t)*start[1]+obj.t*end[1]),
                     int((1-obj.t)*start[2]+obj.t*end[2])]
        if len(start) == 4 and len(end) == 4:
            obj.radius = start[3] * (1 - ps(obj)) + end[3] * ps(obj)
        return
    obj.radius = start[0] * (1 - ps(obj)) + end[0] * ps(obj)

def ps(obj):
    if obj.s and not obj.t3:
        return obj.t*obj.t*(3-2*obj.t)
    elif obj.s and obj.ts:
        if obj.vel == 1:
            return obj.t**3
        return 1 - (1 - obj.t)**3
    return obj.t

def setUp(obj, color, t, start, end) -> None:
    obj.color, obj.ts, obj.start, obj.end = color, t, start, end