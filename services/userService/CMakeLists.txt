
add_subdirectory(modules)

add_executable(userService)
target_link_libraries(userService userServiceModules)
target_sources(userService PRIVATE
    main.cpp
    serviceConnect.cpp
)
