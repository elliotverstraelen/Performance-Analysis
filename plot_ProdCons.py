#!/usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np
import pandas


csv = pandas.read_csv("csv/pro_con.csv")
print(csv)

# mean
csv.dropna(axis=0, how='any', thresh=None, subset=None, inplace=False)
mean = csv.groupby(["thread number"]).mean()["time"]
std = csv.groupby(["thread number"]).std()["time"]
threads = csv["thread number"].unique()

print("\n mean : \n")
print(mean)
print("\n standard deviation : \n")
print(std)
print("\n threads : \n")
print(threads)

fig1 = plt.figure()
plt.plot(threads, mean, color="blue", linewidth=1.0, linestyle="-")
plt.errorbar(threads, mean, yerr=std, fmt="-o")

plt.xlim(0,25)
plt.xticks(np.linspace(0,24,13))
plt.xlabel('Nombre de threads')
plt.ylim(0,11000)
plt.yticks(np.linspace(0, 11000, 11))

plt.ylabel('Time (ms)')
plt.title('Avgerage time of execution of ./producteurs-consomateurs.c')
plt.savefig("pro_con_graph.png")

plt.show()

# Closing the plot.
plt.close()
