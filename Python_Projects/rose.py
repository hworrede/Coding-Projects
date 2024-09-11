import matplotlib.pyplot as plt 
from matplotlib.widgets import Slider  
import numpy as np

n=3
d=2
k = n / d

measurement = np.linspace(0, 2 * np.pi, 1000)


final_value = np.cos(k * measurement)

y_coordinate = final_value * np.sin(measurement)
x_coordinate = final_value * np.cos(measurement)  
  
fig, ax = plt.subplots()
(line,) = plt.plot(x_coordinate, y_coordinate)

plt.subplots_adjust(left=0.3, bottom=0.3)
d_axis = plt.axes([0.25, 0.15, 0.70, 0.02])
n_axis = plt.axes([0.25, 0.18, 0.70, 0.02])

slider_nvalue = Slider(
    ax=n_axis,  
    label="Value of n",  
    valmin=1,  
    valmax=7,  
    valinit=n,  
)

slider_dvalue = Slider(
    ax=d_axis, 
    label="Value of d",  
    valmin=1,  
    valmax=9,  
    valinit=d,  
)

def update(val):
	d = slider_dvalue.val
	n = slider_nvalue.val
	k = n / d
	
	final_value = np.cos(k * measurement)
	x_coordinate = final_value * np.cos(measurement)
	y_coordinate = final_value * np.sin(measurement)
	
	line.set_xdata(x_coordinate)
	line.set_ydata(y_coordinate)
	fig.canvas.draw_idle()
slider_nvalue.on_changed(update)
slider_dvalue.on_changed(update)

ax.axis()
plt.show()