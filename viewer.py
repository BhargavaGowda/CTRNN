import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("out.txt")
plt.plot(data[:,1])
plt.show()