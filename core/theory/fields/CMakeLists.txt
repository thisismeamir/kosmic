add_library(KosmicTheoryFields STATIC
  src/TheoryFields.cpp
)

target_include_directories(
  KosmicTheoryFields PUBLIC
  include
)

target_link_libraries(KosmicTheoryFields PUBLIC KosmicField KosmicMath)
