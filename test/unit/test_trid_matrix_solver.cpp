// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#include <tridiagonal_matrix/trid_matrix.hpp>
#include <tridiagonal_matrix/trid_solver.hpp>
#include <test_utils.hpp>
#include <gtest/gtest.h>
#include <vector>

void testNaiveSolveDoublePrecision(const int n)
{
  auto matrix = TridiagonalMatrix<double>(n, static_cast<std::size_t>(711), static_cast<double>(-10.0), static_cast<double>(4.0)); // generate a tridiagonal matrix
  std::vector<double> b(n); // right-hand side
  std::vector<double> x(n); // solution
  std::fill(b.begin(), b.end(), static_cast<double>(1.0)); // initialize the right-hand side with arbitrary values; using random values leads to less accurate solution
  NaiveSolve<double>(matrix, b, x); // call the naive tridiaonal matrix solver
  double rel_tolerance = 2e-11; // relative tolerance for double precision
  auto b_test = matrix.ComputeAx(x);
  verify<double>(b_test, b, rel_tolerance);
}

void testNaiveSolveSinglePrecision(const int n)
{
  auto matrix = TridiagonalMatrix<float>(n, static_cast<std::size_t>(711), static_cast<float>(-10.0), static_cast<float>(4.0)); // generate a tridiagonal matrix
  std::vector<float> b(n); // right-hand side
  std::vector<float> x(n); // solution
  std::fill(b.begin(), b.end(), static_cast<float>(1.0)); // initialize the right-hand side with arbitrary values; using random values leads to less accurate solution
  NaiveSolve<float>(matrix, b, x); // call the naive tridiaonal matrix solver
  float rel_tolerance = 2e-2; // relative tolerance for single precision
  auto b_test = matrix.ComputeAx(x);
  verify<float>(b_test, b, rel_tolerance);
}

TEST(TridMatrixSolver, NaiveImplementationDoublePrecision)
{
  testNaiveSolveDoublePrecision(10);
  testNaiveSolveDoublePrecision(100);
  testNaiveSolveDoublePrecision(1000);
  testNaiveSolveDoublePrecision(10000);
  testNaiveSolveDoublePrecision(100000);
}

TEST(TridMatrixSolver, NaiveImplementationSinglePrecision)
{
  testNaiveSolveSinglePrecision(10);
  testNaiveSolveSinglePrecision(100);
  testNaiveSolveSinglePrecision(1000);
  testNaiveSolveSinglePrecision(10000);
  testNaiveSolveSinglePrecision(100000);
}