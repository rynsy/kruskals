## Kruskals Minimum Spanning Tree
### an implementation in C++

This is my implementation of [Kruskals Minimum Spanning Tree](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm). I wrote this program years ago and decided to clean it up a bit and throw it on Github. I've lost the original test data that I was using to prove the algorithm's correctness, but there are scripts for generating random test data. There's also an [IPython notebook](https://github.com/rynsy/kruskals/blob/master/analysis/Algorithm%20dataplot.ipynb) that graphs runtimes of the algorithm and shows that the algorithm is **O( E log E )**.

#### Compilation and testing:
```
    make
    make test
    make random_test TESTS=[number of tests to run]
```
There is an IPython notebook with graphs showing my results from running
100 randomly generated test cases. The script that generates test cases
is located at random\_tests/test\_maker.py
