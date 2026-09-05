add_library(kosmic_backend_cpu STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_backend_cpu PUBLIC include)
target_link_libraries(kosmic_backend_cpu PUBLIC kosmic_integrator kosmic_field)
