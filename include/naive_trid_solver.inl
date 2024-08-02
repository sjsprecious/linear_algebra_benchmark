// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#include <stdexcept>

// overloaded constructor that takes the size of the matrix as input argument;
// the default constructor will use the length of 10
inline naive_trid_solver::naive_trid_solver(int n = 10) : length(n)
{
    dl = new DTYPE[n-1]; // sub-diagonal
    d = new DTYPE[n]; // diagonal
    du = new DTYPE[n-1]; // super-diagonal
    b = new DTYPE[n]; // right-hand side & solution vector
    b_ref = new DTYPE[n]; // reference right-hand side

    // Check for successful allocations
    if (!dl || !d || !du || !b || !b_ref)
    {
        throw std::runtime_error("Memory allocation failed");
    }

    // Initialize to some arbitrary values
    for (int i = 0; i < n - 1; i++)
    {
        dl[i] = -1.0; // sub-diagonal elements
        du[i] = -1.0; // super-diagonal elements
    }
    for (int i = 0; i < n; i++)
    {
        d[i] = 2.0; // diagonal elements
        b[i] = 1.0; // right-hand side values
    }
}

// destructor
inline naive_trid_solver::~naive_trid_solver()
{
    // free allocated memory
    delete[] dl;
    delete[] d;
    delete[] du;
    delete[] b;
    delete[] b_ref;
}

// solve the tridiagonal matrix system
inline void naive_trid_solver::solve()
{
    // Solve the system A * x = b
    for (int i = 1; i < length; i++)
    {
        DTYPE m = dl[i - 1] / d[i - 1];
        d[i] -= m * du[i - 1];
        b[i] -= m * b[i - 1];
    }
    b[length - 1] = b[length - 1] / d[length - 1];
    for (int i = length - 2; i >= 0; i--)
    {
        b[i] = (b[i] - du[i] * b[i + 1]) / d[i];
    }
}