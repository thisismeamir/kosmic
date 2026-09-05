add_library(kosmic_math STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_math PUBLIC include)
target_link_libraries(kosmic_math PUBLIC BLAS::BLAS LAPACK::LAPACK GSL::gsl FFTW3::fftw3)
