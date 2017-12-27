cmake_minimum_required (VERSION 2.8)
project (SSYBlockchain)

# Version Number

set (SSYBC_VERSION_MAJOR 0)
set (SSYBC_VERSION_MINOR 1)

# C++ Compiler Flag

SET(CPP_STANDARD_COMPILE_FLAGS "-std=c++11")
add_definitions(${CPP_STANDARD_COMPILE_FLAGS})

# Configuration File

set(CONFIG_HEADER ${PROJECT_SOURCE_DIR}/include/ssybc/config/ssybc_config.hpp)
configure_file (
  "${PROJECT_SOURCE_DIR}/include/ssybc/config/ssybc_config.hpp.in"
  ${CONFIG_HEADER}
)

# CMake Option

option (
  SSYBC_BUILD_SAMPLES
  "Enable CUDA for GPU mining." ON
)

option (
  SSYBC_ENABLE_CUDA
  "Enable CUDA for GPU mining." OFF
)


# Macro

macro(subdir_list result curdir)
  file(GLOB children relative ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      list(append dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

macro(filelist result curdir)
  file(GLOB children relative ${curdir} ${curdir}/*)
  set(flist "")
  foreach(child ${children})
    if(not IS_DIRECTORY ${curdir}/${child})
      list(append flist ${child})
    endif()
  endforeach()
  set(${result} ${flist})
endmacro()

# Configure Options

if (SSYBC_BUILD_SAMPLES)
  subdir_list(sample_dirs "${PROJECT_SOURCE_DIR}/samples")
  foreach(sample_dir ${sample_dirs})
    add_subdirectory(${sample_dir})
    filelist(sample_files ${sample_dir})
    foreach(sample_file ${sample_files})
      add_executable(SSYBlockchain ${sample_file})
    endforeach()
  endforeach()
endif (SSYBC_BUILD_SAMPLES)


# Create Library

file(GLOB SSYBC_SRC_FILES
    "*.h"
    "*.hpp"
)

set(SSYBC_HEADER_FILE ${PROJECT_SOURCE_DIR}/include/ssybc/ssybc.hpp)

# add_library(ssy_blockchain SSYBC_SRC_FILES)

# install (TARGETS ssy_blockchain DESTINATION bin)
# install (FILES SSYBC_SRC_FILES DESTINATION include)

# target_link_libraries (SSYBlockchain ssy_blockchain)

# add the install targets
add_executable (SSYBlockchain ${PROJECT_SOURCE_DIR}/samples/sample_01_cpu_string/sample_01_cpu_string.cpp)
install (TARGETS SSYBlockchain DESTINATION bin)
