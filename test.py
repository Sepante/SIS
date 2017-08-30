import matplotlib.pyplot as plt
import numpy as np

data = np.random.normal(size=10000)
plt.hist(data, bins=np.logspace(0.1, 1.0, 50))
plt.gca().set_xscale("log")
plt.show()
