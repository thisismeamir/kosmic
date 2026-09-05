
add_executable(FreeScalarRun main.cpp)
target_link_libraries(FreeScalarRun PRIVATE
  KosmicField
  KosmicGeometry
  KosmicTheoryInterface
  KosmicTheoryFields
  KosmicTemplateFreeScalar
  KosmicIntegrator
)
 

