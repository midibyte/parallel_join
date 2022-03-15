parallel join

This program implements a parallel algorithm for the SQL JOIN operation.
The goal is to show the potential performance that can be gained by implementing a parallelized algorithm.
The speedup is shown by running a single threaded algorithm and the parallel algorithm on the same dataset and comparing their runtimes.

requirements:
    make
    g++ with C++11 support

to compile the program run make

to run the program use:
    parallel_join tableOneSize tableTwoSize threadCount

    NOTE: threadCount must be greater than 1
