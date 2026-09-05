add_library(KosmicField STATIC
  src/Field.cpp
)
target_include_directories(KosmicField PUBLIC include)
target_link_libraries(KosmicField PUBLIC KosmicMath)
