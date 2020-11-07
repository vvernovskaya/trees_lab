import csv
import matplotlib.pyplot as plt
import math
import numpy as np


def extract_csv_into_array(file_name, row_num):
    array_tmp = []
    with open(file_name) as f:
        csv_in = csv.reader(f)
        for row in csv_in:
            array_tmp.append(int(row[row_num]))

    return array_tmp


def make_plot(x_data, y_data, title, color):
    x_label = "Tree size"
    y_label = "Time"

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


sizes = extract_csv_into_array("output_times_insert.csv", 0)
times_insert = extract_csv_into_array("output_times_insert.csv", 1)
times_find = extract_csv_into_array("output_times_find.csv", 1)
times_erase = extract_csv_into_array("output_times_erase.csv", 1)

make_plot(sizes, times_insert, "Asymptotic complexity of inserting", 'purple')
make_plot(sizes, times_find, "Asymptotic complexity of searching", 'blue')
make_plot(sizes, times_erase, "Asymptotic complexity of erasing", 'green')



