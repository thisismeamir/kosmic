add_library(kosmic_backend_cuda STATIC
    src/placeholder.cu
)
target_include_directories(kosmic_backend_cuda PUBLIC include)
target_link_libraries(kosmic_backend_cuda PUBLIC kosmic_integrator kosmic_field CUDA::cudart CUDA::cublas CUDA::cufft)
set_target_properties(kosmic_backend_cuda PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
