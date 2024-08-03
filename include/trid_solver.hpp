// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vector>

// solve the tridiagonal matrix system with a naive algorithm
template<typename T>
void NaiveSolve(const TridiagonalMatrix<T>& matrix, const std::vector<T>& b, std::vector<T>& x);

#include "trid_solver.inl"