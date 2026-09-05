add_library(kosmic_storage_schema STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_storage_schema PUBLIC include)
target_link_libraries(kosmic_storage_schema PUBLIC ${HDF5_CXX_LIBRARIES})
target_include_directories(kosmic_storage_schema PUBLIC ${HDF5_INCLUDE_DIRS})
