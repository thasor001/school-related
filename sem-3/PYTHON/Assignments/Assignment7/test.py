

import numpy as np

px = np.array([1.0,2.0,3.0,4.0])
py = np.array([1.0,2.0,4.0,5.0])

x1, x2 = np.meshgrid(px, px)
y1, y2 = np.meshgrid(py, py)

avstander = (x1-x2) + (y1-y2)

print(px)
print(avstander)