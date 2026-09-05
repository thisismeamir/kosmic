add_library(KosmicIntegrator STATIC
    src/placeholder.cpp
)
target_include_directories(KosmicIntegrator PUBLIC include)
target_link_libraries(KosmicIntegrator PUBLIC KosmicTheoryInterface KosmicField)
