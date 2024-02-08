from sympy import symbols, pi, S
from numpy import array


M_vw = [[S(25)/29, S(10)/29],
        [S(10)/29, S(4)/29]]

# TASK 2d)

vec_x = [S(3), S(5)]


def matCVec(mat, vec):
    return [S(vec[0]) * S(mat[j][0]) + S(vec[1]) * S(mat[j][1]) for j in range(len(mat))]


print(matCVec(M_vw, vec_x))