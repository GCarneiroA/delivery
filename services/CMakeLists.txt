
add_subdirectory(modules)

add_executable(serviceConfig serviceConfig.cpp)
target_link_libraries(serviceConfig serviceConfigModules)
