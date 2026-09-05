add_library(kosmic_amr STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_amr PUBLIC include)
target_link_libraries(kosmic_amr PUBLIC kosmic_field kosmic_theory_interface)
