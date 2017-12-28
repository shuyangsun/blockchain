cmake_minimum_required (VERSION 2.8)

# Version Number

set (SSYBC_VERSION_MAJOR 0)
set (SSYBC_VERSION_MINOR 2)
set (SSYBC_VERSION_BUILD 1)

project (SSYBlockchain DESCRIPTION "Generic purpose lightweight blockchain library.")

# C++ Compiler Flag

set(CPP_COMPILER_FLAGS "-std=c++14")

# Platform and Library Requirement Check

include (CheckCXXSourceCompiles)

CHECK_CXX_SOURCE_COMPILES ("
  #include <atomic>
  struct Dummy { int val; };
  int main() {
    std::atomic<struct Dummy> dummy = Dummy();
    int val = dummy.load().val;
    return 0;
  }
" SSYBC_HAS_ATOMIC_FOR_CUSTOM_TYPE)

CHECK_CXX_SOURCE_COMPILES ("
  #include <time.h>
  int main() { struct tm ptm; time_t t; gmtime_s(&t, &ptm); return 0; }
" SSYBC_HAS_C11_GMTIME_S)

CHECK_CXX_SOURCE_COMPILES ("
  #include <time.h>
  int main() { struct tm ptm; time_t t; gmtime_s(&ptm, &t); return 0; }
" SSYBC_HAS_WIN32_GMTIME_S)

CHECK_CXX_SOURCE_COMPILES ("
  #include <time.h>
  int main() { struct tm ptm; time_t t; gmtime_r(&t, &ptm); return 0; }
" SSYBC_HAS_UNIX_GMTIME_R)

find_package (Threads)

# Configuration File

configure_file (
  "${PROJECT_SOURCE_DIR}/include/ssybc/config/ssybc_config.hpp.in"
  "${PROJECT_SOURCE_DIR}/include/ssybc/config/ssybc_config.hpp"
)

# CMake Option

option (
  BUILD_SAMPLES
  "Enable CUDA for GPU mining." ON
)

option (
  ENABLE_CUDA
  "Enable CUDA for GPU mining." OFF
)

if(ENABLE_CUDA)
  set(SSYBC_IS_CUDA_ENABLED "SSYBC_IS_CUDA_ENABLED")
endif(ENABLE_CUDA)


# Macro


macro(get_header_files result curdir)
  file(GLOB_RECURSE res
    "${curdir}/*.h"
    "${curdir}/*.h++"
    "${curdir}/*.hpp"
  )
  set(${result} ${res})
endmacro()


macro(get_source_files result curdir)
  get_header_files(res ${curdir})
  file(GLOB_RECURSE res_srcs
    "${curdir}/*.c"
    "${curdir}/*.cc"
    "${curdir}/*.cpp"
  )

  list(APPEND res ${res_srcs})

  if(ENABLE_CUDA)
    file(GLOB_RECURSE res_cuda "${curdir}/*.cu")
    list(APPEND res ${res_cuda})
  endif(ENABLE_CUDA)

  set(${result} ${res})
endmacro()


macro(get_subdir_list result curdir format)
  FILE(GLOB children "${curdir}/${format}")
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()


# Get Header and Source Files

set(SSYBC_HPP "${PROJECT_SOURCE_DIR}/include/ssybc/ssybc.hpp")
set(SSYBC_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SSYBC_LIBRARY_DIR "${PROJECT_SOURCE_DIR}/library")
set(SSYBC_SRC_DIR "${PROJECT_SOURCE_DIR}/src")

get_header_files(SSYBC_HEADER_FILES ${SSYBC_INCLUDE_DIR})
get_source_files(SSYBC_LIB_FILES ${SSYBC_LIBRARY_DIR})
get_source_files(SSYBC_SRC_FILES ${SSYBC_SRC_DIR})

# Create Library

add_library(SSYBlockchain STATIC ${SSYBC_HEADER_FILES} ${SSYBC_LIB_FILES} ${SSYBC_SRC_FILES})
target_link_libraries (SSYBlockchain ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(SSYBlockchain PUBLIC ${PROJECT_SOURCE_DIR})
target_compile_options( SSYBlockchain PUBLIC ${CPP_COMPILER_FLAGS} )

install (TARGETS SSYBlockchain DESTINATION bin)
install (FILES ${SSYBC_HPP} DESTINATION include)

# Add Sample Projects

if (BUILD_SAMPLES)
  set(ssybc_samples_dir "${PROJECT_SOURCE_DIR}/samples")
  get_subdir_list(ssybc_sample_subdirs ${ssybc_samples_dir} "*cpu*")
  
  if (ENABLE_CUDA)
    get_subdir_list(ssybc_cuda_sample_dirs ${ssybc_samples_dir} "*cuda*")
    list(APPEND ssybc_sample_subdirs ${ssybc_cuda_sample_dirs})
  endif(ENABLE_CUDA)

  foreach(dir ${ssybc_sample_subdirs})
    add_subdirectory (${dir})
  endforeach()
endif (BUILD_SAMPLES)
