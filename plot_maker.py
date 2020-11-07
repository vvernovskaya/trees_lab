import csv
import matplotlib.pyplot as plt
import math
import numpy as np

sizes = []
times = []

file_name = "output_data_2.csv"

with open(file_name) as f:
    csv_in = csv.reader(f)
    for row in csv_in:
        sizes.append(int(row[0]))
        times.append(float(row[1]))

fig, ax = plt.subplots(figsize=(7, 7))

x_data = sizes
y_data = times
title = "Asymptotic complexity of inserting an element into a tree"
x_label = "Tree size"
y_label = "Time"

print(type(sizes[0]))
print(type(times[0]))

ax.scatter(x=x_data, y=y_data, marker='o', c='purple', edgecolor='b')
ax.set_title(title)
ax.set_xlabel(x_label)
ax.set_ylabel(y_label)
ax.set_xlim(xmin=min(x_data) - abs(max(x_data) - min(x_data)) * 0.1,
            xmax=max(x_data) + abs(max(x_data) - min(x_data)) * 0.1)
ax.set_ylim(ymin=min(y_data) - abs(max(y_data) - min(y_data)) * 0.1,
            ymax=max(y_data) + abs(max(y_data) - min(y_data)) * 0.1)

#x = np.linspace(0, max(x_data), 1000)
#ax.plot(x, calc_b(x_data, y_data) * x + calc_a(x_data, y_data), 'r--')

fig.tight_layout()

plt.show()
