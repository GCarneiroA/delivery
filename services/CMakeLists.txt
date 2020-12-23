
add_subdirectory(userService)
add_subdirectory(serviceConnect)

add_executable(serviceConnect)
target_sources(serviceConnect PRIVATE
    main.cpp
    serviceConnect.cpp
)
target_link_libraries(serviceConnect serviceConnectModules)
