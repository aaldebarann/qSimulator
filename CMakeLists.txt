cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME qSimulator)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

set(Q_LIBRARY "${PROJECT_NAME}")
set(Q_TESTS   "test_${PROJECT_NAME}")
set(Q_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(Q_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")

include_directories("${Q_INCLUDE}" gtest)

# BUILD
add_subdirectory(src)
add_subdirectory(samples)
add_subdirectory(test)
add_subdirectory(gtest)

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")