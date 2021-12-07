#!/usr/bin/env python3

# Exemple d'utilisation de la librairie python matplotlib pour LINFO1252

# On importe numpy (pour se faciliter la vie) et matplotlib
import matplotlib.pyplot as plt
import numpy as np
import pandas

csv = pandas.read_csv("../csv/philo.csv")
print(csv)

# moyenne
mean = csv.groupby(["thread"]).mean()["time"]
std = csv.groupby(["thread"]).std()["time"]
threads = csv["thread"].unique()

print(mean)
print(std)
print(threads)

fig1 = plt.figure()
plt.plot(threads, mean, color="blue", linewidth=1.0, linestyle="-")
plt.errorbar(threads, mean, yerr=std, fmt="-o")

plt.xlim(0,25)
plt.xticks(np.linspace(0,24,13))
plt.xlabel('Nombre de threads')
plt.ylim(0,1000)
plt.yticks(np.linspace(0, 1000, 11))

plt.ylabel('Time (ms)')
plt.title('Avg. time of execution of ./philo')
plt.savefig("philo_graph.png")

plt.show()

# On ferme proprement le plot.
plt.close()
