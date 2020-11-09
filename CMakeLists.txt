

cmake_minimum_required(VERSION 3.18)

project(delivery VERSION 0.0.1)

add_subdirectory(dependencies)

# Set binaries output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(cmake)

find_package(Protobuf)

add_subdirectory(services)
add_subdirectory(examples)
