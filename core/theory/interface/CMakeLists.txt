add_library(kosmic_theory_interface STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_theory_interface PUBLIC include)
target_link_libraries(kosmic_theory_interface PUBLIC kosmic_field kosmic_geometry)
