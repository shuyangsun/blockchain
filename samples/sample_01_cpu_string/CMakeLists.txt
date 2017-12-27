add_executable(sample_01_cpu_string sample_01_cpu_string.cpp)

target_link_libraries (sample_01_cpu_string LINK_PUBLIC SSYBlockchain)
target_include_directories(sample_01_cpu_string PRIVATE ${PROJECT_SOURCE_DIR})
target_compile_options( sample_01_cpu_string PUBLIC ${CPP_STANDARD_COMPILE_FLAGS} )
