add_library(kosmic_augment_cluster STATIC
    src/placeholder.cpp
)
target_include_directories(kosmic_augment_cluster PUBLIC include)
target_link_libraries(kosmic_augment_cluster PUBLIC kosmic_storage_manager)
