import matplotlib.pyplot as plt 

height = [float(x) for x in open("graph.txt", "r").read().split("\n")]

label = [str(x) for x in range(10, 510, 10)]

plt.plot(label, height)

plt.show() 