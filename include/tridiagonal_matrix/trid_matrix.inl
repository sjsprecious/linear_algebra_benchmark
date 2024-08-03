// Copyright (C) 2023-2024 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0

// Overloaded constructor that takes the size of the matrix as input argument;
template<typename T>
inline TridiagonalMatrix<T>::TridiagonalMatrix(const int n) : 
        length_(n), dl_(n-1), d_(n), du_(n-1)
{
#if random_init
    // Initialize all the elements to random values
    std::lognormal_distribution<double> distribution(10.0, 4.0); // Define the log-normal distribution with mean 10.0 and standard deviation 4.0 
    unsigned int seed = 12345; // Create a random engine with a specific seed
    std::default_random_engine engine(seed);
    auto get_double = std::bind(distribution, engine); // Bind the distribution to the random engine
    std::ranges::generate(dl_, get_double); // sub-diagonal elements
    std::ranges::generate(du_, get_double); // super-diagonal elements
    std::ranges::generate(d_, get_double); // diagonal elements
#else
    // Initialize all the elements to some arbitrary values; somehow this leads to less accurate solution
    std::fill(dl_.begin(), dl_.end(), static_cast<T>(-1.0)); // sub-diagonal elements
    std::fill(du_.begin(), du_.end(), static_cast<T>(-1.0)); // super-diagonal elements
    std::fill(d_.begin(), d_.end(), static_cast<T>(2.0)); // diagonal elements
#endif
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