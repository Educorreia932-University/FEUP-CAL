import matplotlib.pyplot as plt 
from math import log2

def big_o_order(V, E):
    return (V + E) * log2(V)

real_height = [float(x) for x in open("graph.txt", "r").read().split("\n")]

expected_height = [big_o_order(n ** 2, 4 * n * (n - 1)) for n in range(1, 11)]

label = [str(x) for x in range(1, 11)]

plt.plot(label, real_height)
plt.plot(label, expected_height)
plt.legend(("Real time", "Expected time"))

plt.show() 