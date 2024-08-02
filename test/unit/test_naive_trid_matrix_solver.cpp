// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#include <naive_trid_solver.hpp>
#include <gtest/gtest.h>

void testNaiveTridSolver(const int n)
{
  auto solver = naive_trid_solver(n);
  solver.solve();
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