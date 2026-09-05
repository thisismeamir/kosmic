add_library(KosmicMath STATIC
    src/placeholder.cpp
)
target_include_directories(KosmicMath PUBLIC include)
target_link_libraries(KosmicMath PUBLIC
  BLAS::BLAS
  LAPACK::LAPACK
  GSL::gsl
  KosmicField
)
