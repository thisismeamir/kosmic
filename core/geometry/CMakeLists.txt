add_library(KosmicGeometry
  STATIC
  src/placeholder.cpp
)


target_include_directories(KosmicGeometry PUBLIC include)
target_link_libraries(KosmicGeometry PUBLIC
  KosmicMath
)
