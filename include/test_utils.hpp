// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <gtest/gtest.h>

// verify two vectors with a relative tolerance
template<typename T>
void verify(const std::vector<T>& vector_test, const std::vector<T>& vector_base, T rel_tolerance)
{
  ASSERT_EQ(vector_test.size(), vector_base.size());
  std::size_t vector_size = vector_test.size();
  for (int i = 0; i < vector_size; i++)
  {
    EXPECT_LT(std::abs((vector_test[i] - vector_base[i]) / vector_base[i]), rel_tolerance);
  }
}