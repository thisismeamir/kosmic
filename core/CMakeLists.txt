# core: the simulation kernel. Each subdirectory below is built as its own
# object/static library so module boundaries stay real at the build level,
# not just in folder layout.

add_subdirectory(math)
add_subdirectory(field)
add_subdirectory(geometry)
add_subdirectory(theory)
add_subdirectory(integrator)
add_subdirectory(backend)
add_subdirectory(amr)
add_subdirectory(api)
