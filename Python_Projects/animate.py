import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from random import randint
axis_y = []
axis_x = []
fig, plot_axis = plt.subplots()
def line_plot(i):
    plot = randint(1,10) 
    axis_x.append(i)
    axis_y.append(plot)
    plot_axis.clear()
    plot_axis.plot(axis_x, axis_y)
    plot_axis.set_xlim([0,20])
    plot_axis.set_ylim([0,15])
anima = FuncAnimation(fig, line_plot, frames=20, interval=500, repeat=False)
plt.show()