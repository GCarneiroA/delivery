

cmake_minimum_required(VERSION 3.18)

project(delivery VERSION 0.0.1)

add_subdirectory(dependencies)
add_subdirectory(cmake)

find_package(Protobuf)

add_subdirectory(include)
add_subdirectory(services)
add_subdirectory(applications)


