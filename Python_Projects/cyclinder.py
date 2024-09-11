import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d

def main_cylinder(first_cylin, r1):
    main_figure = plt.figure()
    a1 = np.linspace(0, r1, 40)
    ax = main_figure.add_subplot(1, 1, 1, projection='3d')
    a2 = np.linspace(0, 2 * np.pi, 100)
    final_theta, a1 = np.meshgrid(a2, a1)
    x_main = first_cylin * np.cos(final_theta) 
    y_main = first_cylin * np.sin(final_theta)
    ax.contour3D(x_main,y_main,a1, 70)
    ax.set_title('Image of Cylinder')
    plt.show()

if __name__ == '__main__':
    main_cylinder(2, 10)
    
    