Unit and benchmark tests for linear algebra libraries
==========================

[![License](https://img.shields.io/github/license/sjsprecious/linear_algebra_benchmark.svg)](https://github.com/sjsprecious/linear_algebra_benchmark/blob/master/LICENSE)
[![Docker builds](https://github.com/sjsprecious/linear_algebra_benchmark/actions/workflows/docker_and_coverage.yml/badge.svg)](https://github.com/sjsprecious/linear_algebra_benchmark/actions/workflows/docker_and_coverage.yml)
[![Windows](https://github.com/sjsprecious/linear_algebra_benchmark/actions/workflows/windows.yml/badge.svg)](https://github.com/sjsprecious/linear_algebra_benchmark/actions/workflows/windows.yml)
[![Mac](https://github.com/sjsprecious/linear_algebra_benchmark/actions/workflows/mac.yml/badge.svg)](https://github.com/sjsprecious/linear_algebra_benchmark/actions/workflows/mac.yml)
[![Ubuntu](https://github.com/sjsprecious/linear_algebra_benchmark/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/sjsprecious/linear_algebra_benchmark/actions/workflows/ubuntu.yml)
[![codecov](https://codecov.io/gh/sjsprecious/linear_algebra_benchmark/graph/badge.svg?token=9wXiwTjZb8)](https://codecov.io/gh/sjsprecious/linear_algebra_benchmark)

# 1. Basic installation (without any linear algebra library)
To build and install this repo without enabling any linear algebra library on NCAR's HPC (e.g., Derecho), you need to open a terminal window, navigate to a scratch directory, and load the following modules first:

```
module purge
module load gcc/13.2.0
module load cmake/3.26.3
module load ncarcompilers/1.0.0
```

Then you can do:

```
git clone git@github.com:sjsprecious/linear_algebra_benchmark.git
cd linear_algebra_benchmark 
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D ENABLE_UNIT_TESTS=ON -D ENABLE_BENCHMARK_TESTS=ON .. 
make -j 8
```

Once the compilation succeeds, you can run the tests by:

```
make test
```

An example output looks like:

```
Running tests...
Test project /glade/derecho/scratch/sunjian/linear_algebra_benchmark/build
    Start 1: unit_trid_matrix_solver
1/2 Test #1: unit_trid_matrix_solver ..........   Passed    0.04 sec
    Start 2: performance_trid_matrix_solver
2/2 Test #2: performance_trid_matrix_solver ...   Passed   35.12 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =  35.35 sec
```