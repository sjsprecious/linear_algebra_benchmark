// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#pragma once

#if USE_DOUBLE
#define DTYPE double 
#else
#define DTYPE float 
#endif

class naive_trid_solver
{
    private:
        int length; // size of the diagonal
        DTYPE *dl; // sub-diagonal
        DTYPE *d; // diagonal
        DTYPE *d_ref; // reference diagonal
        DTYPE *du; // super-diagonal
        DTYPE *b; // right-hand side & solution vector
        DTYPE *b_ref; // reference right-hand side
    public:
        naive_trid_solver() = delete; // delete the default constructor
        naive_trid_solver(const int n); // overloaded constructor that takes the size of the matrix as input argument
        void solve(); // solve the tridiagonal matrix system
        ~naive_trid_solver(); // destructor
        void display(); // display the tridiagonal matrix
        void verify(); // verify the solution
        // naive_trid_solver(const naive_trid_solver&) = default; // use default copy constructor
        // naive_trid_solver& operator=(const naive_trid_solver&) = default; // use default copy assignment operator
        // naive_trid_solver(naive_trid_solver&& other) = default; // use default move constructor
        // naive_trid_solver& operator=(naive_trid_solver&& other) = default; // use default move assignment operator
};

#include "naive_trid_solver.inl"