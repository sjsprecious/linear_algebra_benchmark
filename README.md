Unit and benchmark tests for some linear algebra libraries
==========================

# Basic installation (without any linear algebra library)
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