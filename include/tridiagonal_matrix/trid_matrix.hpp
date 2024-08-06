// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

template<typename T>
class TridiagonalMatrix
{
 public:
  int length_;  // size of the diagonal
  // using std::vector<T> does not need a destructor; it frees automatically
  std::vector<T> dl_;                           // sub-diagonal
  std::vector<T> d_;                            // diagonal
  std::vector<T> du_;                           // super-diagonal
  TridiagonalMatrix() = delete;                 // delete the default constructor
  TridiagonalMatrix(const int n, const T val);  // overloaded constructor that takes the size of the matrix "n" and fixed
                                                // initial value "val" for all elements of dl_, d_ and du_
  TridiagonalMatrix(
      const int n,
      const T dl_val,
      const T d_val,
      const T du_val);  // overloaded constructor that takes the size of the matrix "n" and different fixed initial value for
                        // dl_, d_ and du_
  TridiagonalMatrix(
      const int n,
      const std::size_t random_number_seed,
      const T mean,
      const T stddev);  // overloaded constructor that takes the size of the matrix "n" and a seed value for random initial
                        // values of all elements of dl_, d_ and du_
  std::vector<T> ComputeAx(const std::vector<T>& x) const;  // compute the product of the tridiagonal matrix and a vector
  void Display() const;                                     // display the tridiagonal matrix
  // naive_trid_solver(const naive_trid_solver&) = default; // use default copy constructor
  // naive_trid_solver& operator=(const naive_trid_solver&) = default; // use default copy assignment operator
  // naive_trid_solver(naive_trid_solver&& other) = default; // use default move constructor
  // naive_trid_solver& operator=(naive_trid_solver&& other) = default; // use default move assignment operator
};

#include "trid_matrix.inl"