// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <iomanip>
#include <algorithm>

// Overloaded constructor that takes the size of the matrix as input argument;
template<typename T>
inline TridiagonalMatrix<T>::TridiagonalMatrix(const int n) : 
        length_(n), dl_(n-1), d_(n), du_(n-1)
{
    // Initialize to some arbitrary values
    std::fill(dl_.begin(), dl_.end(), static_cast<T>(-1.0)); // sub-diagonal elements
    std::fill(du_.begin(), du_.end(), static_cast<T>(-1.0)); // super-diagonal elements
    std::fill(d_.begin(), d_.end(), static_cast<T>(2.0)); // diagonal elements
}

// Display the tridiagonal matrix
inline void TridiagonalMatrix::Display() const
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