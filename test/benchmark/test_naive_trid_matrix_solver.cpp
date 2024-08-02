// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#include <naive_trid_solver.hpp>
#include <benchmark/benchmark.h>

#include <random>
#include <vector>

const unsigned RANDOM_NUMBER_SEED = 123;

// Define a fixture class for the benchmark
class BenchmarkFixture : public benchmark::Fixture
{
};

// @brief Define a benchmark function to test the naive tridiagonal matrix solver
// @param state Benchmarking argument
BENCHMARK_DEFINE_F(BenchmarkFixture, BM_NAIVE_TRID_SOLVER)
(benchmark::State& state)
{
  for (auto _ : state)
  {
    state.PauseTiming();
    auto solver = naive_trid_solver(state.range(0));
    state.ResumeTiming();
    solver.solve();
  }
}

// @brief Register the functions defined above with different number of grid cells
BENCHMARK_REGISTER_F(BenchmarkFixture, BM_NAIVE_TRID_SOLVER)->Unit(benchmark::kMillisecond)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000);

// @brief Main function to run the benchmarks
BENCHMARK_MAIN();