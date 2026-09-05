add_library(kosmic_api STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_api PUBLIC include)
target_link_libraries(kosmic_api PUBLIC
    kosmic_field
    kosmic_geometry
    kosmic_theory_interface
    kosmic_theory_abelian_higgs
    kosmic_integrator
    kosmic_backend_cpu
    kosmic_amr
)
# This is Kosmic's one deliberately-versioned public surface: bindings
# (Kotlin orchestration, later) are written against these headers only.
set_target_properties(kosmic_api PROPERTIES VERSION ${PROJECT_VERSION})
