import numpy as np
import matplotlib.pyplot as plt

def mandelbrot( h,w, maxiter=50 ):
    """Returns an image of the Mandelbrot fractal of size (h,w)."""
    y,x = np.ogrid[ -1.4:1.4:h*1j, -2:0.8:w*1j ]    # make two vectors x and y
    y = y.T
    x = x.T
    c = x+y*1j                                       # make a 2D array of complex numbers
    z = c
    divtime = maxiter + np.zeros(z.shape, dtype=int) # make a pixel map

    for i in range(maxiter):
        z = z**2 + c                            # update z, the 2D array of complex numbers
        diverge = z*np.conj(z) > 2**2           # find all diverging points, diverge is a Boolean 2D array
        div_now = diverge & (divtime==maxiter)  # find now diverging points
        divtime[div_now] = i                    # update the pixel map
        z[diverge] = 2                          # avoid diverging too much

    return divtime

img = mandelbrot(400,400)
plt.imshow(img)
plt.imsave("mandelbrot.png", img)
plt.show()