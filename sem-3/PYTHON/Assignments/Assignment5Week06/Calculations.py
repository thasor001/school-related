import numpy as np

matA = np.zeros((10, 10))
matA[:, 4] = 1
matA[3:5, :] = 1

matB = np.zeros((10, 10))
matB[1:9, 1:9] = 1

matC = matA + matB
print(matC)

matD = np.array([[True if item > 1 else False for item in matC[i, :]] for i in range(len(matC))])

print(matD)