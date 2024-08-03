// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#include <naive_trid_solver.hpp>
#include <gtest/gtest.h>

// verify the solution
template<typename T>
void naive_trid_solver::verify()
{
    // Compute the result of A*x
    // A*x = d[i]*x[i] + du[i]*x[i+1] + dl[i-1]*x[i-1]
    DTYPE* res = new DTYPE[length]; // result of A*x
    for (int i = 0; i < length; i++)
    {
        res[i] = d_ref[i] * b[i];
        if (i > 0)
        {
            res[i] += dl[i - 1] * b[i - 1];
        }
        if (i < length - 1)
        {
            res[i] += du[i] * b[i + 1];
        }
    }
    // Check the solution with the reference right-hand side
    for (int i = 0; i < length; i++)
    {
        EXPECT_LT(std::abs((res[i] - b_ref[i]) / b_ref[i]), rel_tolerance);
    }
    delete[] res;
}

void testNaiveTridSolver(const int n)
{
  auto solver = naive_trid_solver(n);
  solver.solve();
  solve<double>(xxxx);
  solver.verify();
}

TEST(TridMatrixSolver, NaiveImplementation)
{
  testNaiveTridSolver(10);
//  testNaiveTridSolver(100);
//  testNaiveTridSolver(1000);
//  testNaiveTridSolver(10000);
//  testNaiveTridSolver(100000); 
}