add_library(kosmic_field STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_field PUBLIC include)
target_link_libraries(kosmic_field PUBLIC kosmic_math)
