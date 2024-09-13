
#
# Get GoogleTest dependency
#

cmake_minimum_required(VERSION 3.15)

include(FetchContent)
message(STATUS "Building tests")
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#
# Setup to reach include and source files to be tested.
#

# Add base include directory.
message(STATUS "Building trm tests")
set(TEST_NAME trm_tests)

file(GLOB_RECURSE SRC *.cpp)

add_executable(${TEST_NAME}
    ${SRC}
)

find_package(Threads REQUIRED)

target_include_directories(${TEST_NAME} PUBLIC
  "../include"
  "."
)

target_link_libraries(${TEST_NAME} PUBLIC
  ${CMAKE_DL_LIBS}
  Threads::Threads
)

target_compile_options(${TEST_NAME} PRIVATE
    -Wall
    -Wextra
    -Wconversion
    -Wsign-conversion
    -Wnon-virtual-dtor
    -Wreturn-type
    -Werror
)

# Require C++17
target_compile_features(${TEST_NAME} PUBLIC cxx_std_17)

target_link_libraries(${TEST_NAME}
  PRIVATE
    GTest::gtest
    gmock
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
