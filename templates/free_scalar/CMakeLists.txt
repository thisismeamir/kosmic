add_library(KosmicTemplateFreeScalar STATIC
  src/FreeScalarDynamics.cpp
)
target_include_directories(
  KosmicTemplateFreeScalar PUBLIC
  include
)
target_link_libraries(KosmicTemplateFreeScalar PUBLIC
  KosmicField
  KosmicGeometry
  KosmicTheoryInterface
  KosmicTheoryFields
  KosmicMath
)
