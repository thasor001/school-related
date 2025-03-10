from numpy import array
from sympy import sin, cos, pi, sqrt, symbols, S


def cross(u, v):
    return array([
        u[1]*v[2] - u[2] * v[1],
        -(u[0]*v[2] - u[2] * v[0]),
        u[0]*v[1] - u[1] * v[0]
    ])


def length(u):
    return sqrt(sum(u[i]**2 for i in range(len(u))))


def dot(u, v):
    return sum([u[i] * v[i] for i in range(len(u))])


def project(u, v):
    return array([dot(u, v) / length(v)**2 * v[j] for j in range(2)])


def matXvec(u, m):
    return array([sum(u[j] * m[i, j] for j in range(len(u))) for i in range(len(m))])


def matRotation(u, angle):
    matrix = array([
        [cos(angle), -sin(angle)],
        [sin(angle), cos(angle)]
    ])
    return array([u[0]*matrix[i, 0] + u[1]*matrix[i, 1] for i in range(len(u))])


def matXmat(m1, m2):
    return array([[sum([m * m2[i, x]for i, (m) in enumerate(m1[j])])for x in range(len(m1))]for j in range(len(m2))])


def mul(k, v):
    return array([k*v[i] for i in range(len(v))])


def vecvec(u, v):
    return array([u[i] + v[i] for i in range(len(u))])


def matmat(m1, m2):
    return array([[m1[j, i] + m2[j, i] for i in range(len(m1))] for j in range(len(m2))])


u = array([3, 4])

mat = array([[S(9/34), S(15/34)], [S(15/34), S()]])


u = array([1, 1])
v1 = array([2, 5])
v2 = array([-5, 4])
v3 = array([1,2,3])
v4 = array([1,2,3])
vectorX = array([1, 0])
vectorY = array([0, 1])
matrix1 = array([
    project(vectorX, u),
    project(vectorY, u)
])

mat1 = array([
    [1,2,3],
    [4,5,6],
    [7,8,9]
])

mat2 = array([
    [1,2,3],
    [1,2,3],
    [1,2,3]
])


mat3 = array([
    [1, 2],
    [6, 7]
])

mat4 = array([
    [1, 3],
    [3, 4]
])

matX = array([
    [1, 0, 0],
    [0, -1, 0],
    [0, 0, 1]
])

mat1 = array([
    [0, 2],
    [3, 0]
])

mat2 = array([
    [1, 0],
    [0, -1]
])

mat3 = array([
    [cos(-pi/4), -sin(-pi/4)],
    [sin(-pi/4), cos(-pi/4)]
])

a1 = matXmat(mat1, mat2)

b1 = matXmat(a1, mat3)

mat4 = array([
    [0, 1],
    [1, 0]
])

u = array([2, 6, 2])

mat1 = array([
    [1, 2, 3],
    [1, 2, 3],
    [4, 5, 6]
])

a, b, c, alpha = symbols("a b c alpha")

mat5 = array([
    [a/(sqrt(a**2+b**2)), b/(sqrt(a**2+b**2)), 0],
    [-b/(sqrt(a**2+b**2)), a/(sqrt(a**2+b**2)), 0],
    [0, 0, 1]
])

vec4 = array([a, b, c])

mat6 = array([
    [a**2/sqrt(a**2 + b**2) + b**2/sqrt(a**2 + b**2), 0, c],
    [0, 1, 0],
    [-c, 0, a**2/sqrt(a**2 + b**2) + b**2/sqrt(a**2 + b**2)]
])



vec42 = array([a**2/sqrt(a**2 + b**2) + b**2/sqrt(a**2 + b**2), 0, c])

b4 = matXvec(vec4, mat5)


d4 = matXvec(vec42, mat6)

vectorX = array([
    1, 0, 0
])
vectorY = array([
    0, 1, 0
])
vectorZ = array([
    0, 0, 1
])

mat5 = array([
    cross(vec4, vectorX),
    cross(vec4, vectorY),
    cross(vec4, vectorZ)
])

mat6 = matXmat(mat5, mat5)

matI = array([
    [1, 0, 0],
    [0, 1, 0],
    [0, 0, 1]
])

# v = x, y and z vector u = a b c
# (cos(t) * v + (1-cos(t)) * dot(u,v)) * u

u = array([
    a, b, c
])

part1X = mul(cos(alpha), vectorX)
part1Y = mul(cos(alpha), vectorY)
part1Z = mul(cos(alpha), vectorZ)

part2X = mul(((1 - cos(alpha)) * dot(u, vectorX)), u)
part2Y = mul(((1 - cos(alpha)) * dot(u, vectorY)), u)
part2Z = mul(((1 - cos(alpha)) * dot(u, vectorZ)), u)

solX = vecvec(part1X, part2X)
solY = vecvec(part1Y, part2Y)
solZ = vecvec(part1Z, part2Z)

mattest1 = array([
    [1,2],
    [3,4]
])
mattest2 = array([
    [2,1],
    [4,3]
])


# print(matmat(matI, mul((1-cos(alpha)), mat6)))
