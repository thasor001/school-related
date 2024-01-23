import sympy as sp

'''Task 1'''
#print(sp.sin(sp.pi/10))

#print(sp.cos(sp.pi/8))

#x = sp.symbols("x")
#print(sp.solve(x**2 - 2*x - 3, x))

#vectorU = [sp.sqrt(2)/2, 2]
#vectorV = [3, sp.sqrt(5)]


def twodotProduct(u, v):
    return u[0] * v[0] + u[1] * v[1]

#print(twodotProduct(vectorU, vectorV))


def twovectorLength(vector):
    return sp.sqrt(vector[0]**2 + vector[1]**2)

#print(twovectorLength(vectorU))


def twounitvector(vector, length):
    return [vector[0]/length, vector[1]/length]

#print(twounitvector(vectorU, twovectorLength(vectorU)))

'''Task 2'''
#vectorU = [1, 1, -1]
#vectorV = [2, 5, 2]


def threevectorLength(vectorU):
    return sp.sqrt(vectorU[0]**2 + vectorU[1]**2 + vectorU[2]**2)

#print(threevectorLength(vectorV))


def threevectorProduct(vectorU, vectorV):
    return vectorU[0] * vectorV[0] + vectorU[1] * vectorV[1] + vectorU[2] * vectorV[2]

#print(threevectorProduct(vectorU, vectorV))


def crossProduct(U, V):
    X = U[1] * V[2] - U[2] * V[1]
    Y = -(U[0] * V[2] - U[2] * V[0])
    Z = U[0] * V[1] - U[1] * V[0]
    product = [X, Y, Z]
    return product

#print(crossProduct(vectorU, vectorV))

#print(crossProduct(vectorV, vectorU))

#vectorN = crossProduct(vectorU, vectorV)

#print(threevectorLength(vectorN))

#print(threevectorLength(crossProduct(vectorU, vectorV))/(threevectorLength(vectorU)*threevectorLength(vectorV)))


'''Task 3'''

#arr = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24]

def counter(someList):
    counter = 0
    for i in range(len(someList)):
        if someList[i] % 2 == 1:
            counter += 1
    return counter

#print(counter(arr))


'''Task 4'''
import math as m

vectorU = [1, 2, 3]
vectorV = [4, 5, 6]

def add (u, v):
    x = u[0] + v[0]
    y = u[1] + v[1]
    z = u[2] + v[2]
    return [x, y, z]

def multiply(k, v):
    x = k[0] * v[0]
    y = k[1] * v[1]
    z = k[2] * v[2]
    return [x, y, z]

def dot(u, v):
    x = u[0] * v[0]
    y = u[1] * v[1]
    z = u[2] * v[2]
    return [x, y, z]

def vabs(u):
    return m.sqrt(u[0]**2+u[1]**2+u[2]**2)

