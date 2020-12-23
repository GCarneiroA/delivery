
add_subdirectory(modules)

add_executable(serviceConnect)
target_link_libraries(serviceConnect serviceConnectModules)
target_sources(serviceConnect PRIVATE
    main.cpp
    serviceConnect.cpp
)
