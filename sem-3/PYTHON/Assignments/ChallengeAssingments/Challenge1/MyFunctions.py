from Challenge1 import myCircle


def quadBezier(obj):
    myCircle.move(
        obj,
        (obj.start[0] * (1 - s(obj)) ** 2 + 2 * obj.control[0] * s(obj) * (1 - s(obj)) + obj.end[0] * s(obj) ** 2),
        (obj.start[1] * (1 - s(obj)) ** 2 + 2 * obj.control[1] * s(obj) * (1 - s(obj)) + obj.end[1] * s(obj) ** 2)
    )

def quadBezierColor(obj):
    for i in range(obj.numberTriangles):
        obj.triangles[i].color = (
            min(255, max(0, int(obj.start_Colors[i][0] * (1 - obj.tc) ** 3 + 3 * (1 - obj.tc) ** 2 * obj.tc * 100 + 3 * (1 - obj.tc) * obj.tc ** 2 * 120 + obj.tc ** 3 * (obj.start_Colors[i][0] - 100)))),
            min(255, max(0, int(obj.start_Colors[i][1] * (1 - obj.tc) ** 3 + 3 * (1 - obj.tc) ** 2 * obj.tc * 35 + 3 * (1 - obj.tc) * obj.tc ** 2 * 70*2 + obj.tc ** 3 * 220))),
            min(255, max(0, int(obj.start_Colors[i][2] * (1 - obj.tc) ** 3 + 3 * (1 - obj.tc) ** 2 * obj.tc * 240*2 + 3 * (1 - obj.tc) * obj.tc ** 2 * 180 + obj.tc ** 3 * (obj.start_Colors[i][2] - 75))))
        )


def s(obj):
    if obj.ts:
        return obj.t*obj.t*(3-2*obj.t)
    else:
        return obj.t

def followMouse(obj, mousePos):
    distX, distY = mousePos[0] - obj.center[0], mousePos[1] - obj.center[1]
    ratio = min(1, 2 / max(1, max(abs(distX), abs(distY))))

    myCircle.move(
        obj,
        obj.center[0] + distX * ratio * 3,
        obj.center[1] + distY * ratio * 3
    )

def posUptade(shape, dt):
    shape.t += dt * shape.vel
    if shape.t > 1:
        shape.direction *= -1
        shape.t = 1
        shape.vel *= -1
    elif shape.t < 0:
        shape.direction *= -1
        shape.t = 0
        shape.vel *= -1
