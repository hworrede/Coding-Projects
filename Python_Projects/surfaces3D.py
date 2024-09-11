import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

def paraboloid_hyper():
    ax = plt.axes(projection='3d')
    x = np.linspace(-1, 1, 30)
    y = np.linspace(-1, 1, 30)
    X, Y = np.meshgrid(x, y)
    a,b = 0.5,1
    V = X*X/a - Y*Y/b
    ax.contour3D(X, Y, V, 50)
    ax.set_title('Image of Hyperbolic Paraboloid')
    plt.show()

def paraboloid_ellip():
    ax = plt.axes(projection='3d')
    x = np.linspace(-1, 1, 30)
    y = np.linspace(-1, 1, 30)
    X, Y = np.meshgrid(x, y)
    a,b = 0.5,1
    V = a*X*X + b*Y*Y
    ax.contour3D(X, Y, V, 50)
    ax.set_title('Image of Elliptical Paraboloid')
    plt.show()

def cone():
    ax = plt.axes(projection='3d')
    theta1 = np.linspace(0, 2*np.pi, 100)
    r1 = np.linspace(-2, 0, 100)
    t1, R1 = np.meshgrid(theta1, r1)

    first_x = R1*np.cos(t1)
    first_y = R1*np.sin(t1)
    first_z = 5+R1*2.5

    theta2 = np.linspace(0, 2*np.pi, 100)
    r2 = np.linspace(0, 2, 100)
    t2, R2 = np.meshgrid(theta2, r2)
    second_x = R2*np.cos(t2)
    second_y = R2*np.sin(t2)
    second_z = -5+R2*2.5
 
    ax.plot_surface(first_x, first_y, first_z, alpha=0.9, color="red")
    ax.set_title('Image of Cone')

    plt.show()
    
def sphere():
    ax = plt.axes(projection='3d')
    first_value = np.linspace(0, 2 * np.pi, 100)
    second_value = np.linspace(0, np.pi, 100)
    x = 8 * np.outer(np.cos(first_value), np.sin(second_value))
    y = 8 * np.outer(np.sin(first_value), np.sin(second_value))
    V = 8 * np.outer(np.ones_like(first_value), np.cos(second_value))
    ax.plot_surface(x, y, V,  rstride=6, cstride=6)
    ax.set_title('Image of Sphere')
    plt.show()
    
def parallelopipe():
    plot_arrays = np.array([[-1, -1, -1],[1, -1, -1 ],[1, 1, -1],[-1, 1, -1],[-1, -1, 1],[1, -1, 1 ],[1, 1, 1],[-1, 1, 1]])

    points = [[3, 1, -3],[1, 3, -2 ],[1, 1, -3]]
    V = np.zeros((8,3))
    for i in range(8): V[i,:] = np.dot(plot_arrays[i,:],points)
    V = 10.0*V

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    r = [-1,1]

    X, Y = np.meshgrid(r, r)
    ax.scatter3D(V[:, 0], V[:, 1], V[:, 2])

    final_sides = [[V[0],V[1],V[2],V[3]],
    [V[4],V[5],V[6],V[7]], 
    [V[0],V[1],V[5],V[4]], 
    [V[2],V[3],V[7],V[6]], 
    [V[1],V[2],V[6],V[5]],
    [V[4],V[7],V[3],V[0]]]

    ax.add_collection3d(Poly3DCollection(final_sides, 
    facecolors='green', linewidths=2, edgecolors='b', alpha=.25))
    ax.set_title('Image of Parallopiped')
    plt.show()


def pyramid():
    ax = plt.axes(projection='3d')
    second_value = np.array([[-1, -1, -1], [1, -1, -1], [1, 1, -1],  [-1, 1, -1], [0, 0, 1]])
    ax.scatter3D(second_value[:, 0], second_value[:, 1], second_value[:, 2])
    
    final_sides = [ [second_value[0],second_value[1],second_value[4]], [second_value[0],second_value[3],second_value[4]],[second_value[2],second_value[1],second_value[4]], [second_value[2],second_value[3],second_value[4]], [second_value[0],second_value[1],second_value[2],second_value[3]]]

    ax.add_collection3d(Poly3DCollection(final_sides, facecolors='red', linewidths=1, edgecolors='b', alpha=.25))
    ax.set_title('Image of Pyramid')

    plt.show()

def hyperboloid_ellip():
    A = np.array([[1,0,0],[0,2,0],[0,0,2]])
    center = [0,0,0]

    first_value, s, rotation = np.linalg.svd(A)
    radii = 1.0/np.sqrt(s)

    first_value = np.linspace(0.0, 2.0 * np.pi, 100)
    second_value = np.linspace(0.0, np.pi, 100)
    x = radii[0] * np.outer(np.cos(first_value), np.sin(second_value))
    y = radii[1] * np.outer(np.sin(first_value), np.sin(second_value))
    V = radii[2] * np.outer(np.ones_like(first_value), np.cos(second_value))
    for i in range(len(x)):
        for j in range(len(x)):
            [x[i,j],y[i,j],V[i,j]] = np.dot([x[i,j],y[i,j],V[i,j]], rotation) + center
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_wireframe(x, y, V,  rstride=6, cstride=6, color='r', alpha=0.5)
    ax.set_title('Image of Elliptical Hyperboloid')
    plt.show()

def hyperboloid_hyper():
    ax = plt.axes(projection='3d')
    r=1
    first_value=np.linspace(-2,2,150)
    second_value=np.linspace(0,2*np.pi,50)
    [first_value,second_value]=np.meshgrid(first_value,second_value)
    a = 1
    b = 1
    c = 1
    V = c*np.sinh(first_value)
    y = b*np.cosh(first_value)*np.sin(second_value)
    x = a*np.cosh(first_value)*np.cos(second_value)
   

    ax.plot_surface(x, y, V,  rstride=6, cstride=6)
    ax.set_title('Image of Hyperbolic Hyperboloid')
    plt.show()
    



    
# parallelopipe()
# pyramid()
# sphere()
cone()
# hyperboloid_ellip()
# hyperboloid_hyper()
# paraboloid_ellip()
# paraboloid_hyper()