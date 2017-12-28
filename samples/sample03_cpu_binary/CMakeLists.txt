
get_filename_component(sample_prj_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
get_source_files(source_files ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${sample_prj_name} ${source_files})

target_link_libraries (${sample_prj_name} LINK_PUBLIC SSYBlockchain)
target_include_directories(${sample_prj_name} PRIVATE ${PROJECT_SOURCE_DIR})
target_compile_options( ${sample_prj_name} PUBLIC ${CPP_COMPILER_FLAGS} )
