add_library(kosmic_integrator STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_integrator PUBLIC include)
target_link_libraries(kosmic_integrator PUBLIC kosmic_theory_interface kosmic_field)
