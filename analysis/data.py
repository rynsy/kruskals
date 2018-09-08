# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <headingcell level=1>

# Analysis of "Stay on budget" algorithm Runtime

# <markdowncell>

# In this notebook, we'll be looking at the runtime and number of comparisons made by my solution to the stamps problem. During the execution of the algorithm, there is a counter in place to tally the number of comparisons made by the algorithm. At the end of execution, the size of the input, number of comparisons, and runtime of the algorithm are written to a file. For my analysis, I used a script to create 6 test cases. Each test case has 10^x elements, with x ranging from 1 to 6. Below I plot out the number of comparisons made for each of these test cases and plot them against 3 other functions for comparisons. 

# <codecell>

import numpy as np
import matplotlib.pyplot as plt
import test_analysis as ta
import math


t = np.arange(1., 1000000., 100.)

#data is formated : [ [size of sequence, num of comparisons, runtime], ...]
data = ta.prep_data("results.txt")

size = []
comp = []
runtime = []

for i in data:
    size.append(i[0])
    comp.append(i[1])
    runtime.append(i[2])

    
# red dashes, blue squares and green triangles
plt.xlabel('Size of input')
plt.ylabel('Number of comparisons (tens of millions)')

log, = plt.plot(t,  t*log2(t), 'g' , label="nlog(n)", linewidth=1.0)
res, = plt.plot(size, comp, 'b', label="Results", linewidth=1.0)
lin, = plt.plot(t, 3*t, 'y', label="3*n", linewidth=1.0)
com, = plt.plot(t, 3*t*log2(t), 'r', label="n**2", linewidth=1.0)

plt.legend( [res, log, lin, com], ['results', 'n * log(n)', '3 * n', '3 * n * log(n)'], loc=2)

plt.grid(True)
plt.show()

# <rawcell>

# As you can see, the growth of the number of comparisons made by the algorithm are comparable to the number of comparisons made for a n * log(n) solution. The constant 3 is dropped in Big-Oh notation, so the algorithm is on the order of n * log(n). Below is a graph that plots the runtime of the algorithm against the size of the input for the algorithm. 

# <codecell>

plt.ylabel('Runtime (seconds)')
plt.xlabel('Size of input')
plt.plot(size, runtime, 'r')
plt.grid(True)
plt.show()

