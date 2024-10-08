// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#include <benchmark/benchmark.h>
#include <tridiagonal_matrix/trid_matrix.hpp>
#include <tridiagonal_matrix/trid_solver.hpp>

#include <vector>

// Define a fixture class for the benchmark
class BenchmarkFixture : public benchmark::Fixture
{
};

// @brief Define a benchmark function to test the naive tridiagonal matrix solver with double precision
// @param state Benchmarking argument
BENCHMARK_DEFINE_F(BenchmarkFixture, BM_NAIVE_TRID_SOLVER_DOUBLE_PRECISION)
(benchmark::State& state)
{
  for (auto _ : state)
  {
    state.PauseTiming();
    auto matrix = TridiagonalMatrix<double>(
        state.range(0),
        static_cast<std::size_t>(711),
        static_cast<double>(-10.0),
        static_cast<double>(4.0));                            // generate a tridiagonal matrix
    std::vector<double> b(state.range(0));                    // right-hand side
    std::vector<double> x(state.range(0));                    // solution
    std::fill(b.begin(), b.end(), static_cast<double>(1.0));  // initialize the right-hand side
    state.ResumeTiming();
    NaiveSolve<double>(matrix, b, x);  // call the naive tridiaonal matrix solver
  }
}

// @brief Register the functions defined above with different number of grid cells
BENCHMARK_REGISTER_F(BenchmarkFixture, BM_NAIVE_TRID_SOLVER_DOUBLE_PRECISION)
    ->Unit(benchmark::kMillisecond)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000);

// @brief Define a benchmark function to test the naive tridiagonal matrix solver with single precision
// @param state Benchmarking argument
BENCHMARK_DEFINE_F(BenchmarkFixture, BM_NAIVE_TRID_SOLVER_SINGLE_PRECISION)
(benchmark::State& state)
{
  for (auto _ : state)
  {
    state.PauseTiming();
    auto matrix = TridiagonalMatrix<float>(
        state.range(0),
        static_cast<std::size_t>(711),
        static_cast<float>(-10.0),
        static_cast<float>(4.0));                            // generate a tridiagonal matrix
    std::vector<float> b(state.range(0));                    // right-hand side
    std::vector<float> x(state.range(0));                    // solution
    std::fill(b.begin(), b.end(), static_cast<float>(1.0));  // initialize the right-hand side
    state.ResumeTiming();
    NaiveSolve<float>(matrix, b, x);  // call the naive tridiaonal matrix solver
  }
}

// @brief Register the functions defined above with different number of grid cells
BENCHMARK_REGISTER_F(BenchmarkFixture, BM_NAIVE_TRID_SOLVER_SINGLE_PRECISION)
    ->Unit(benchmark::kMillisecond)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000);

// @brief Main function to run the benchmarks
BENCHMARK_MAIN();