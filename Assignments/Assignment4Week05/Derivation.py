from sympy import *
from numpy import array

t, B, A, C, D = symbols("t B A C D")

expr = t**3 + 8*t

# print((expr.subs("t", 5.3)-expr.subs("t", 4.7))/0.6)


def numDer(f, t, dt):
    return N((f.subs("t", t+dt) - f.subs("t", t-dt))/(2*dt))


def vecDer(vec):
    return [diff(v, t) for v in vec]


vec = array([t*cos(t**2), t**2])

# print(vecDer(vec))

expr2 = sin(t)

# print(numDer(expr2, 1, 0.1))

expr3 = E ** t

# print(numDer(expr3, 2, 0.3))

expr4 = sin(t) + cos(t)

# print(numDer(expr4, 2, 0.1))


vec1 = array([t**2-t, t**4+3*t])

# print(vecDer(vec1))

# print(vecDer(vecDer(vec1)))

expr5 = A*(1-t)**3+3*B*((1-t)**2)*t+3*C*(1-t)*t**2+D*t**3

ph = diff(expr5, t)

print(ph.subs("t", 1))
