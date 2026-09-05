cmake_minimum_required(VERSION 3.20)

project(Kosmic
    VERSION 0.1.0
    DESCRIPTION "General lattice field theory simulation framework"
    LANGUAGES CXX
)

# ---------------------------------------------------------------------------
# Global settings
# ---------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

option(KOSMIC_ENABLE_CUDA "Build the CUDA backend" OFF)
option(KOSMIC_BUILD_TESTS "Build unit and regression tests" ON)
option(KOSMIC_BUILD_AUGMENT "Build the augmentation module" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# ---------------------------------------------------------------------------
# Dependencies
#
# Prefer established, efficient libraries over hand-written implementations
# wherever one exists (BLAS/LAPACK for dense linear algebra, GSL for special
# functions, FFTW for transforms, HDF5 for snapshot storage).
# ---------------------------------------------------------------------------

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(GSL REQUIRED)
find_package(FFTW3 REQUIRED)
find_package(HDF5 REQUIRED COMPONENTS CXX)

if(KOSMIC_ENABLE_CUDA)
    enable_language(CUDA)
    find_package(CUDAToolkit REQUIRED)
endif()

# ---------------------------------------------------------------------------
# Core modules
# ---------------------------------------------------------------------------

add_subdirectory(core)
add_subdirectory(storage)
add_subdirectory(templates)
add_subdirectory(examples)
if(KOSMIC_BUILD_AUGMENT)
    add_subdirectory(augment)
endif()

if(KOSMIC_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# orchestration/ (Kotlin) and sbi/ (Mojo) are deferred and intentionally
# not wired into this build yet.
