// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

// Overloaded constructor that takes the size of the matrix "n" and fixed initial value "val" for all elements of dl_, d_ and du_
template<typename T>
inline TridiagonalMatrix<T>::TridiagonalMatrix(const int n, const T val) :
        length_(n), dl_(n-1, val), d_(n, val), du_(n-1, val) {}

// Overloaded constructor that takes the size of the matrix "n" and different fixed initial value for dl_, d_ and du_
template<typename T>
inline TridiagonalMatrix<T>::TridiagonalMatrix(const int n, const T dl_val, const T d_val, const T du_val) :
        length_(n), dl_(n-1, dl_val), d_(n, d_val), du_(n-1, du_val) {}

// Overloaded constructor that takes the size of the matrix "n" and a seed value for random initial values of all elements of dl_, d_ and du_
template<typename T>
inline TridiagonalMatrix<T>::TridiagonalMatrix(const int n, const std::size_t random_number_seed, const T mean, const T stddev) :
        length_(n), dl_(n-1), d_(n), du_(n-1)
{
    // Initialize all the elements to random values
    std::lognormal_distribution<T> distribution(mean, stddev); // Define the log-normal distribution
    std::default_random_engine engine(random_number_seed); // Define the random engine with a seed value
    auto get_number = std::bind(distribution, engine); // Bind the distribution to the random engine
    std::ranges::generate(dl_, get_number); // sub-diagonal elements
    std::ranges::generate(du_, get_number); // super-diagonal elements
    std::ranges::generate(d_, get_number); // diagonal elements
}

// Compute the product of the tridiagonal matrix and a vector
template<typename T>
inline std::vector<T> TridiagonalMatrix<T>::ComputeAx(const std::vector<T>& x) const
{
    // Compute the result of A*x
    // A*x = d[i]*x[i] + du[i]*x[i+1] + dl[i-1]*x[i-1]
    std::vector<T> result(length_, 0.0);
    result[0] = d_[0] * x[0] + du_[0] * x[1];
    for (int i = 1; i < length_ - 1; i++)
    {
        result[i] = dl_[i-1] * x[i-1] + d_[i] * x[i] + du_[i] * x[i+1];
    }
    result[length_-1] = dl_[length_-2] * x[length_-2] + d_[length_-1] * x[length_-1];
    return result;
}

// Display the tridiagonal matrix
template<typename T>
inline void TridiagonalMatrix<T>::Display() const
{
    for (int i = 0; i < length_; i++)
    {
        for (int j = 0; j < length_; j++)
        {
            if (i == j)
                std::cout << std::fixed << std::setprecision(12) << d_[i] << " ";
            else if (i == j + 1)
                std::cout << std::fixed << std::setprecision(12) << dl_[j] << " ";
            else if (i + 1 == j)
                std::cout << std::fixed << std::setprecision(12) << du_[i] << " ";
            else
                std::cout << std::fixed << std::setprecision(2) << 0.0 << " ";
        }
        std::cout << std::endl;
    }
}