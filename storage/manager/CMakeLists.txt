add_library(kosmic_storage_manager STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_storage_manager PUBLIC include)
target_link_libraries(kosmic_storage_manager PUBLIC kosmic_storage_schema)
