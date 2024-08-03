// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

template<typename T>
class TridiagonalMatrix
{
    public:
        int length_; // size of the diagonal
        // using std::vector<T> does not need a destructor; it frees automatically
        std::vector<T> dl_; // sub-diagonal
        std::vector<T> d_; // diagonal
        std::vector<T> du_; // super-diagonal
        std::vector<T> b; // right-hand side & solution vector
        std::vector<T> b_ref; // reference right-hand side
        TridiagonalMatrix() = delete; // delete the default constructor
        TridiagonalMatrix(const int n); // overloaded constructor that takes the size of the matrix as input argument
        void Display() const; // display the tridiagonal matrix
        // naive_trid_solver(const naive_trid_solver&) = default; // use default copy constructor
        // naive_trid_solver& operator=(const naive_trid_solver&) = default; // use default copy assignment operator
        // naive_trid_solver(naive_trid_solver&& other) = default; // use default move constructor
        // naive_trid_solver& operator=(naive_trid_solver&& other) = default; // use default move assignment operator
};

#include "trid_matrix.inl"