import matplotlib.pyplot as plt 

left = range(1, 50)

height = [float(x) for x in open("graph.txt", "r").read().split("\n")]

label = [str(x) for x in range(10, 500, 10)]

plt.bar(left, height, tick_label = label)

plt.show() 