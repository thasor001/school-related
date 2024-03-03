from sympy import N, diff, symbols, sqrt
from numpy import array, meshgrid, shape, clip, transpose

# t, B, A, C, D = symbols("t B A C D")

def numDerivation(f, t, dt):
    return N((f.subs("t", t+dt) - f.subs("t", t-dt))/(2*dt))

def vecDerivation(vec):
    return [diff(v, t) for v in vec]

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

def matXmat(m1, m2):
    return array([[sum([m * m2[i, x]for i, (m) in enumerate(m1[j])])for x in range(len(m1))]for j in range(len(m2))])


def mul(k, v):
    return array([k*v[i] for i in range(len(v))])

def vecPvec(u, v):
    return array([u[i] + v[i] for i in range(len(u))])


def matPmat(m1, m2):
    return array([[m1[j, i] + m2[j, i] for i in range(len(m1))] for j in range(len(m2))])


def brighten():
    global circleColor
    cirlceColor = circleColor * 1/2



