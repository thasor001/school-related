from numpy import *


image = array([1, 0, 0.499, 0.501, 0.489, 0.897])

image[image > 0.501] = 1.0
image[image < 0.499] = 0.0


print(image)
