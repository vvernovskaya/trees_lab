import csv
import matplotlib.pyplot as plt
import math
import numpy as np


def extract_csv_into_array(file_name, row_num):
    array_tmp = []
    with open(file_name) as f:
        csv_in = csv.reader(f)
        if row_num == 0:
            for row in csv_in:
                array_tmp.append(int(row[row_num]))
        else:
            for row in csv_in:
                array_tmp.append(float(row[row_num]))

    return array_tmp


def make_plot(size_u, x_data, y_data, title, color):
    x_label = size_u
    y_label = "Time, $\\mu$s"

    fig, ax = plt.subplots(figsize=(7, 7))
    ax.scatter(x=x_data, y=y_data, marker='o', c=color, edgecolor='b')
    ax.set_title(title)
    ax.set_xlabel(x_label)
    ax.set_ylabel(y_label)
    ax.set_xlim(xmin=min(x_data) - abs(max(x_data) - min(x_data)) * 0.1,
                xmax=max(x_data) + abs(max(x_data) - min(x_data)) * 0.1)
    ax.set_ylim(ymin=min(y_data) - abs(max(y_data) - min(y_data)) * 0.1,
                ymax=max(y_data) + abs(max(y_data) - min(y_data)) * 0.1)

    fig.tight_layout()
    plt.show()


sizes = extract_csv_into_array("output_times_insert_rb.csv", 0)
times_insert = extract_csv_into_array("output_times_insert_rb.csv", 1)
times_find = extract_csv_into_array("output_times_find_rb.csv", 1)
times_erase = extract_csv_into_array("output_times_erase_rb.csv", 1)

make_plot("Tree size, units", sizes, times_insert, "Asymptotic complexity of inserting into RBTree", 'purple')
make_plot("Tree size, units", sizes, times_find, "Asymptotic complexity of searching in RBTree", 'blue')
make_plot("Tree size, units", sizes, times_erase, "Asymptotic complexity of erasing in RBTree", 'green')

print(sizes[0])

for i in range(len(sizes)):
    sizes[i] = np.log(sizes[i])

print(sizes[0])

make_plot("Tree size, log(units)", sizes, times_insert, "Asymptotic complexity of inserting into RBTree (log)", 'purple')
make_plot("Tree size, log(units)", sizes, times_find, "Asymptotic complexity of searching in RBTree (log)", 'blue')
make_plot("Tree size, log(units)", sizes, times_erase, "Asymptotic complexity of erasing in RBTree (log)", 'green')

