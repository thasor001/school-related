import pyglet
from pyglet.window import key  # for key inputs
from pyglet import shapes
import random
import math

window = pyglet.window.Window(960, 540,
                              caption=("Oblig2 Pyglet"))  # size is 960x540, caption of the window is Oblig2 Pyglet
chooseWindow = 0


circles = pyglet.graphics.Batch()
lines = pyglet.graphics.Batch()
pegasusDraw = pyglet.graphics.Batch()  # for drawing pegasus in a batch

circleList = []  # list for containing circles
lineList = []  # list for containing lines
pegasusList = []  # creates list to store pegasus
# body
pegasusBody = shapes.Rectangle(400, 200, 250, 100, color=(150, 180, 198), batch=pegasusDraw)
pegasusList.append(pegasusBody)
# thigh 1-4
pegasusThigh1 = shapes.Rectangle(450, 130, 50, 70, color=(100, 130, 198), batch=pegasusDraw)
pegasusList.append([pegasusThigh1, pegasusBody, pegasusThigh1.x - pegasusBody.x, pegasusThigh1.y - pegasusBody.y])
pegasusThigh2 = shapes.Rectangle(600, 130, 50, 70, color=(100, 130, 198), batch=pegasusDraw)
pegasusList.append([pegasusThigh2, pegasusBody, pegasusThigh2.x - pegasusBody.x, pegasusThigh2.y - pegasusBody.y])
pegasusThigh3 = shapes.Rectangle(550, 130, 50, 70, color=(150, 180, 198), batch=pegasusDraw)
pegasusList.append([pegasusThigh3, pegasusBody, pegasusThigh3.x - pegasusBody.x, pegasusThigh3.y - pegasusBody.y])
pegasusThigh4 = shapes.Rectangle(400, 130, 50, 70, color=(150, 180, 198), batch=pegasusDraw)
pegasusList.append([pegasusThigh4, pegasusBody, pegasusThigh4.x - pegasusBody.x, pegasusThigh4.y - pegasusBody.y])
# leg 1-4, paw 1-4
pegasusLeg1 = shapes.Rectangle(600, 60, 50, 70, color=(100, 130, 198), batch=pegasusDraw)
pegasusList.append([pegasusLeg1, pegasusThigh1, pegasusLeg1.x - pegasusThigh1.x, pegasusLeg1.y - pegasusThigh1.y])
pegasusPaw1 = shapes.Rectangle(600, 40, 50, 20, color=(60, 178, 178), batch=pegasusDraw)
pegasusList.append([pegasusPaw1, pegasusLeg1, pegasusPaw1.x - pegasusLeg1.x, pegasusPaw1.y - pegasusLeg1.y])
pegasusLeg2 = shapes.Rectangle(450, 60, 50, 70, color=(100, 130, 198), batch=pegasusDraw)
pegasusList.append([pegasusLeg2, pegasusThigh2, pegasusLeg2.x - pegasusThigh2.x, pegasusLeg2.y - pegasusThigh2.y])
pegasusPaw2 = shapes.Rectangle(450, 40, 50, 20, color=(60, 178, 178), batch=pegasusDraw)
pegasusList.append([pegasusPaw2, pegasusLeg2, pegasusPaw2.x - pegasusLeg2.x, pegasusPaw2.y - pegasusLeg2.y])
pegasusLeg3 = shapes.Rectangle(550, 60, 50, 70, color=(150, 180, 198), batch=pegasusDraw)
pegasusList.append([pegasusLeg3, pegasusThigh3, pegasusLeg3.x - pegasusThigh3.x, pegasusLeg3.y - pegasusThigh3.y])
pegasusPaw3 = shapes.Rectangle(550, 40, 50, 20, color=(100, 198, 198), batch=pegasusDraw)
pegasusList.append([pegasusPaw3, pegasusLeg3, pegasusPaw3.x - pegasusLeg3.x, pegasusPaw3.y - pegasusLeg3.y])
pegasusLeg4 = shapes.Rectangle(400, 60, 50, 70, color=(150, 180, 198), batch=pegasusDraw)
pegasusList.append([pegasusLeg4, pegasusThigh4, pegasusLeg4.x - pegasusThigh4.x, pegasusLeg4.y - pegasusThigh4.y])
pegasusPaw4 = shapes.Rectangle(400, 40, 50, 20, color=(100, 198, 198), batch=pegasusDraw)
pegasusList.append([pegasusPaw4, pegasusLeg4, pegasusPaw4.x - pegasusLeg4.x, pegasusPaw4.y - pegasusLeg4.y])
# Neck, head
pegasusNeck = shapes.Rectangle(400, 280, 60, 70, color=(150, 180, 198), batch=pegasusDraw)
pegasusNeck.rotation = 350
pegasusList.append([pegasusNeck, pegasusBody, pegasusNeck.x - pegasusBody.x, pegasusNeck.y - pegasusBody.y])
pegasusHead = shapes.Rectangle(340, 290, 120, 65, color=(150, 180, 198), batch=pegasusDraw)
pegasusHead.rotation = 330
pegasusList.append([pegasusHead, pegasusNeck, pegasusHead.x - pegasusNeck.x, pegasusHead.y - pegasusNeck.y])
# tail 1-3
pegasusTail1 = shapes.Rectangle(620, 280, 70, 35, color=(150, 180, 198), batch=pegasusDraw)
pegasusTail1.rotation = 60
pegasusList.append([pegasusTail1, pegasusBody, pegasusTail1.x - pegasusBody.x, pegasusTail1.y - pegasusBody.y])
pegasusTail2 = shapes.Rectangle(640, 235, 55, 35, color=(150, 180, 198), batch=pegasusDraw)
pegasusTail2.rotation = 40
pegasusList.append([pegasusTail2, pegasusTail1, pegasusTail2.x - pegasusTail1.x, pegasusTail2.y - pegasusTail1.y])
pegasusTail3 = shapes.Rectangle(680, 200, 70, 35, color=(150, 180, 198), batch=pegasusDraw)
pegasusTail3.rotation = 20
pegasusList.append([pegasusTail3, pegasusTail2, pegasusTail3.x - pegasusTail2.x, pegasusTail3.y - pegasusTail2.y])
# wing 1-2
pegasusWing2 = shapes.Triangle(480, 200, 500, 430, 680, 430, color=(100, 130, 198), batch=pegasusDraw)
pegasusList.append([pegasusWing2, pegasusBody, pegasusWing2.x - pegasusBody.x, pegasusWing2.y - pegasusBody.y])
pegasusWing1 = shapes.Triangle(460, 200, 480, 430, 660, 430, color=(150, 180, 198), batch=pegasusDraw)
pegasusList.append([pegasusWing1, pegasusBody, pegasusWing1.x - pegasusBody.x, pegasusWing1.y - pegasusBody.y])
# ear 1-2
pegasusEar1 = shapes.Rectangle(396, 396, 10, 20, color=(150, 180, 198), batch=pegasusDraw)
pegasusEar1.rotation = 330
pegasusList.append([pegasusEar1, pegasusHead, pegasusEar1.x - pegasusHead.x, pegasusEar1.y - pegasusHead.y])
pegasusEar2 = shapes.Rectangle(402, 398, 10, 20, color=(100, 130, 198), batch=pegasusDraw)
pegasusEar2.rotation = 330
pegasusList.append([pegasusEar2, pegasusHead, pegasusEar2.x - pegasusHead.x, pegasusEar2.y - pegasusHead.y])


def absv(u):
    return (u[0] ** 2 + u[1] ** 2)**0.5


def dot(u, v):
    x = u[0] * v[0]
    y = u[1] * v[1]
    return x + y


def project(u, v):
    px = dot(u, v) / (absv(v) ** 2) * v[0]
    py = dot(u, v) / (absv(v) ** 2) * v[1]
    return [px, py]


colors = [(0, 0, 255), (255, 0, 0), (0, 255, 0), (0, 255, 255)]


def draw1():
    for index, (crcl) in enumerate(circleList):
        if crcl[0].x >= 960:
            crcl[0].x -= 960  # if the circle is out of the box it will teleport into the other side.
        elif crcl[0].x <= 0:
            crcl[0].x = 960
        if crcl[0].y >= 540:
            crcl[0].y -= 540
        elif crcl[0].y <= 0:
            crcl[0].y = 540

        crcl[0].x += crcl[1] / 60
        crcl[0].y += crcl[2] / 60

        circleList[index][0].color = colors[1]

        for ln in lineList:
            lineVec = [ln[0].x2 - ln[0].x,
                       ln[0].y2 - ln[0].y]  # vector P1 from P2 from a line

            P1toCircle = [crcl[0].x - ln[0].x,
                          crcl[0].y - ln[0].y]  # vector from P1 to circle

            projP1toCircle = project(P1toCircle, lineVec)  # creates projection of p1toCircle onto lineVec

            distance = absv([P1toCircle[0] - projP1toCircle[0], P1toCircle[1] - projP1toCircle[1]])  # length of proj

            if distance <= crcl[0].radius:
                P2toCircle = [crcl[0].x - ln[0].x2,
                              crcl[0].y - ln[0].y2]

                if 0 <= dot(projP1toCircle, lineVec) <= absv(lineVec) ** 2:  # if dot(P1toCircle,lineVec) / dot(lineVec,lineVec) < 0 or dot(P1toCircle,lineVec) / dot(lineVec,lineVec) > 1: <- this is from the assignment but it didnt work
                    circleList[index][0].color = colors[2]

                elif absv(P1toCircle) < crcl[0].radius or absv(P2toCircle) < crcl[0].radius:
                    circleList[index][0].color = colors[2]

        for circleCol in circleList:  # turns circle red upon hitting another circle
            if crcl[0] is not circleCol[0]:
                circleVec = [circleCol[0].x - crcl[0].x,
                             circleCol[0].y - crcl[0].y]

                circleLength = math.sqrt(circleVec[0] ** 2 + circleVec[1] ** 2)

                if circleLength < crcl[0].radius + circleCol[0].radius:
                    circleList[index][0].color = colors[0]

    for ln in lineList:
        ln[0].x += ln[1]/60
        ln[0].y += ln[2]/60
    lines.draw()
    circles.draw()

def draw2():
    pegasusDraw.draw()
    pegasusBody.x += 1 / 60 * pegasusBody.velx  # speed of pegasus loop
    for i in range(1, len(pegasusList)):
        pegasusList[i][0].x = pegasusList[i][1].x + pegasusList[i][2]
        pegasusList[i][0].y = pegasusList[i][1].y + pegasusList[i][3]


@window.event
def on_key_press(symbol, modifiers):
    global chooseWindow

    if symbol == key.SPACE:
        if chooseWindow == 1:
            chooseWindow = 0  # this is for switching between task A and task B
        else:
            chooseWindow = 1


pegasusBody.velx = -3  # speed pegasus is going to be moving

@window.event
def on_draw():
    window.clear()
    if chooseWindow == 0:
        draw1()
    else:
        draw2()

for i in range(10):  # loop to create random circles
    circleList.append([pyglet.shapes.Circle(random.randint(0, 960),
                                            random.randint(0, 540),
                                            random.randint(10, 15),
                                            color=(255, 0, 0),
                                            batch=circles),
                       random.choice([-128, -60, 60, 128]),
                      random.choice([-128, -60, 60, 128])])



for i in range(1):
    lineList.append([pyglet.shapes.Line(x=random.randint(0, 960),
                                        y=random.randint(0, 540),
                                        x2=random.randint(0, 960),
                                        y2=random.randint(0, 540),
                                        color=(255, 255, 255),
                                        batch=lines),
                     random.choice([-128, -60, 60, 128]),
                     random.choice([-128, -60, 60, 128])])

pyglet.app.run()