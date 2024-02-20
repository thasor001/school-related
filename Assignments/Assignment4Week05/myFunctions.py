# update time for circles.
def posUptade(shape, dt) -> None:
    shape.t += dt/shape.ts * shape.vel
    if shape.t > 1 or shape.t < 0:
        shape.vel *= -1

# quadBezier curve.
def quadBezier(obj, start, control, end) -> None:
    obj.x = start[0] * (1-obj.t)**2 + 2 * control[0] * obj.t * (1-obj.t) + end[0] * obj.t**2
    obj.y = start[1] * (1-obj.t)**2 + 2 * control[1] * obj.t * (1-obj.t) + end[1] * obj.t**2

# Linear bezier curve.
def linearBezier(obj, start, end):
    # if start and end length == 2, normal linear beziercurve.
    if len(start) == 2 and len(end) == 2:
        obj.x, obj.y = (start[0]*(1-ps(obj))+end[0]*ps(obj), start[1]*(1-ps(obj))+end[1]*ps(obj))
        return
    # If bigger than 2 color needs to change and not pos.
    elif len(start) > 2 and len(end) > 2:
        obj.color = [max(0, min(255, int((1-obj.t)*start[0]+obj.t*end[0]))),
                     max(0, min(255, int((1-obj.t)*start[1]+obj.t*end[1]))),
                     max(0, min(255, int((1-obj.t)*start[2]+obj.t*end[2])))]
        # if length == 4, color change and radius change.
        if len(start) == 4 and len(end) == 4:
            obj.radius = start[3] * (1 - ps(obj)) + end[3] * ps(obj)
        return
    # if length only 1 only radius change
    obj.radius = start[0] * (1 - ps(obj)) + end[0] * ps(obj)

# time function.
def ps(obj):
    # if obj.s then smoothstep
    if obj.s and not obj.t3:
        return obj.t*obj.t*(3-2*obj.t)
    # if obj.s and obj.t3 then goofy movement to the blue circle.
    elif obj.s and obj.t3:
        if obj.vel == 1:
            return obj.t**3
        return 1 - (1 - obj.t)**3
    # if nothing just return the time.
    return obj.t

# Set up function that sets up the circle classes.
def setUp(obj, color, t, start, end) -> None:
    obj.color, obj.ts, obj.start, obj.end = color, t, start, end
