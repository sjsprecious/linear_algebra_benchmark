// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#include <tridiagonal_matrix/trid_matrix.hpp>
#include <tridiagonal_matrix/trid_solver.hpp>
#include <gtest/gtest.h>
#include <vector>

// verify the solution
template<typename T>
void verify(const TridiagonalMatrix<T>& matrix, const std::vector<T>& b, 
               std::vector<T>& x, T rel_tolerance)
{
    std::vector<T> res(matrix.length_); // result of A*x

    // Compute the result of A*x
    // A*x = d[i]*x[i] + du[i]*x[i+1] + dl[i-1]*x[i-1]
    for (int i = 0; i < matrix.length_; i++)
    {
        res[i] = matrix.d_[i] * x[i];
        if (i > 0)
        {
            res[i] += matrix.dl_[i - 1] * x[i - 1];
        }
        if (i < matrix.length_ - 1)
        {
            res[i] += matrix.du_[i] * x[i + 1];
        }
    }
    // Check the solution with the reference right-hand side
    for (int i = 0; i < matrix.length_; i++)
    {
        EXPECT_LT(std::abs((res[i] - b[i]) / b[i]), rel_tolerance);
    }
}

void testNaiveSolveDoublePrecision(const int n)
{
  auto matrix = TridiagonalMatrix<double>(n); // generate a tridiagonal matrix
  std::vector<double> b(n); // right-hand side
  std::vector<double> x(n); // solution
  std::fill(b.begin(), b.end(), static_cast<double>(1.0)); // initialize the right-hand side
  NaiveSolve<double>(matrix, b, x); // call the naive tridiaonal matrix solver
  double rel_tolerance = 5e-7; // relative tolerance for double precision
  verify<double>(matrix, b, x, rel_tolerance);
}

void testNaiveSolveSinglePrecision(const int n)
{
  auto matrix = TridiagonalMatrix<float>(n); // generate a tridiagonal matrix
  std::vector<float> b(n); // right-hand side
  std::vector<float> x(n); // solution
  std::fill(b.begin(), b.end(), static_cast<float>(1.0)); // initialize the right-hand side
  NaiveSolve<float>(matrix, b, x); // call the naive tridiaonal matrix solver
  float rel_tolerance = 5e-2; // relative tolerance for single precision
  verify<float>(matrix, b, x, rel_tolerance);
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
  testNaiveSolveSinglePrecision(1000); // using a larger matrix size leads to wrong results
}