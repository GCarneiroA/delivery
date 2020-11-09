
add_subdirectory(modules)

add_executable(serviceConfig main.cpp)
target_link_libraries(serviceConfig serviceConfigModules)
