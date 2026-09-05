add_subdirectory(cpu)
if(KOSMIC_ENABLE_CUDA)
    add_subdirectory(cuda)
endif()
