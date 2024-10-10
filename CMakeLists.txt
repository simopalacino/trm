#
# CMake root project for TRM - Thread-safe Reference with Mutex
#

cmake_minimum_required(VERSION 3.15)

project(trm VERSION "0.1.0" LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force out-of-source builds.
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# If build type is not specified, default to Release.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Set build type to Debug or Release (default Release)" FORCE)
  message(STATUS "Set CMAKE_BUILD_TYPE to Release (default)")
endif()

# Only set the cxx_standard if it is not set by someone else
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

#
# Configuration
#
include(GNUInstallDirs)

#
# Tests
#
# enable_testing()
# add_subdirectory(examples)
# add_subdirectory(test)
