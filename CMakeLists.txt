

cmake_minimum_required(VERSION 3.18)

project(delivery VERSION 0.0.1)
configure_file(deliveryVersion.h.in deliveryVersion.h)          # Version configuration file

add_subdirectory(dependencies)

# Set binaries output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(cmake)

find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

add_subdirectory(services)

option(BUILD_APPS "Build the applications" ON)
if (BUILD_APPS)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    find_package(Qt5 COMPONENTS Core Qml Widgets REQUIRED)
    add_subdirectory(apps)
endif()

add_subdirectory(examples)
