// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

// solve the tridiagonal matrix system
template<typename T>
void NaiveSolve(const TridiagonalMatrix<T>& matrix, const std::vector<T>& b, std::vector<T>& x)
{
    std::vector<T> d_tmp(matrix.length_);

    d_tmp[0] = matrix.du_[0] / matrix.d_[0];
    x[0] = b[0] / matrix.d_[0];
    for (int i = 1; i < matrix.length_; i++)
    {
        T denom = static_cast<T>(1.0) / (matrix.d_[i] - matrix.dl_[i-1] * d_tmp[i-1]);
        d_tmp[i] = matrix.du_[i] * denom;
        x[i] = (b[i] - matrix.dl_[i-1] * x[i-1]) * denom;    
    }
    for (int i = matrix.length_ - 2; i >= 0; i--)
    {
        x[i] -= d_tmp[i] * x[i+1];
    }
}