// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <gtest/gtest.h>

#ifdef USE_DOUBLE
const double rel_tolerance = 5.e-7;
#else
const float rel_tolerance = 5.e-6;
#endif

// overloaded constructor that takes the size of the matrix as input argument;
inline naive_trid_solver::naive_trid_solver(const int n) : length(n)
{
    dl = new DTYPE[n-1]; // sub-diagonal
    d = new DTYPE[n]; // diagonal
    d_ref = new DTYPE[n]; // reference diagonal
    du = new DTYPE[n-1]; // super-diagonal
    b = new DTYPE[n]; // right-hand side & solution vector
    b_ref = new DTYPE[n]; // reference right-hand side

    // Check for successful allocations
    if (!dl || !d || !d_ref || !du || !b || !b_ref)
    {
        throw std::runtime_error("Memory allocation failed");
    }
    // Initialize to some arbitrary values
    for (int i = 0; i < n - 1; i++)
    {
        dl[i] = static_cast<DTYPE>(-1.0); // sub-diagonal elements
        du[i] = static_cast<DTYPE>(-1.0); // super-diagonal elements
    }
    for (int i = 0; i < n; i++)
    {
        d[i] = static_cast<DTYPE>(2.0); // diagonal elements
        d_ref[i] = d[i]; // reference diagonal elements
        b[i] = static_cast<DTYPE>(1.0); // right-hand side values
        b_ref[i] = b[i]; // reference right-hand side values
    }
}

// destructor
inline naive_trid_solver::~naive_trid_solver()
{
    // free allocated memory
    if (dl != nullptr) delete[] dl;
    if (d != nullptr) delete[] d;
    if (d_ref != nullptr) delete[] d_ref;
    if (du != nullptr) delete[] du;
    if (b != nullptr) delete[] b;
    if (b_ref != nullptr) delete[] b_ref;
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

// display the tridiagonal matrix
inline void naive_trid_solver::display()
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (i == j)
                std::cout << std::fixed << std::setprecision(12) << d[i] << " ";
            else if (i == j + 1)
                std::cout << std::fixed << std::setprecision(12) << dl[j] << " ";
            else if (i + 1 == j)
                std::cout << std::fixed << std::setprecision(12) << du[i] << " ";
            else
                std::cout << std::fixed << std::setprecision(2) << 0.0 << " ";
        }
        std::cout << std::endl;
    }
}

// verify the solution
inline void naive_trid_solver::verify()
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