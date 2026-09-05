add_library(kosmic_geometry STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_geometry PUBLIC include)
target_link_libraries(kosmic_geometry PUBLIC kosmic_math)
