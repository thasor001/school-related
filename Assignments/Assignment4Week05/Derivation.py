from sympy import *
from numpy import array

t = symbols("t")

expr = t**3 + 8*t

# print((expr.subs("t", 5.3)-expr.subs("t", 4.7))/0.6)

def numDer(f, t, dt):
    return N((f.subs("t", t+dt) - f.subs("t", t-dt))/(2*dt))

def vecDer(vec):
    return [diff(v, t) for v in vec]


vec = array([cos(t), t**2])

# print(vecDer(vec))

expr2 = sin(t)

# print(numDer(expr2, 1, 0.1))

expr3 = E ** t

# print(numDer(expr3, 2, 0.3))

expr4 = sin(t) + cos(t)

# print(numDer(expr4, 2, 0.1))
