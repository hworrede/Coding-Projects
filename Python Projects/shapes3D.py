import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d 

ax = plt.axes(projection='3d')   

x = np.array([0, 1, 1, 0, 0, 1, 1, 0])
y = np.array([0, 0, 1, 1, 0, 0, 1, 1])
z = np.array([0, 0, 0, 0, 1, 1, 1, 1])
ax.scatter3D(x, y, z, s=30, c='b')
ax.plot3D([0, 0], [0, 0], [1, 1], 'r')
ax.plot3D([1, 1], [0, 0], [1, 1], 'r')
ax.plot3D([0, 0], [1, 1], [1, 1], 'r')
ax.plot3D([1, 1], [1, 1], [1, 1], 'r')
ax.plot3D([0, 0], [0, 1], [1, 1], 'r')
ax.plot3D([1, 1], [0, 1], [1, 1], 'r')
ax.plot3D([0, 1], [0, 0], [1, 1], 'r')
ax.plot3D([0, 1], [1, 1], [1, 1], 'r')
ax.plot3D([0, 0], [0, 0], [0, 1], 'r')
ax.plot3D([1, 1], [0, 0], [0, 1], 'r')
ax.plot3D([0, 0], [1, 1], [0, 1], 'r')
ax.plot3D([1, 1], [1, 1], [0, 1], 'r')
ax.plot3D([0, 1], [0, 0], [0, 0], 'r')
ax.plot3D([0, 1], [1, 1], [0, 0], 'r')
ax.plot3D([0, 0], [0, 1], [0, 0], 'r')
ax.plot3D([1, 1], [0, 1], [0, 0], 'r')

ax.set_title('Picture of 3D Cube')
plt.show()                 