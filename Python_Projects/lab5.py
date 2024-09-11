from matplotlib import pyplot as plt
import numpy as np

x = np.linspace(-3, 3, 30)
plt.plot(x, np.sin(x), 'b.')
plt.plot(x, np.cos(x), 'r-')
plt.plot(x, -np.sin(x), 'g--')
plt.title('Trigonometric Functions', fontsize=10)
plt.xlabel('x', fontsize=8)
plt.ylabel('y', fontsize=8)
plt.tick_params(axis='both', labelsize=8)
plt.legend(labels = ('sin(x)', 'cos(x)', '-sin(x)'), loc = 'upper right')
plt.show()            