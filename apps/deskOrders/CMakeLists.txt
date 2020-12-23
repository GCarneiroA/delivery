
include_directories(${PROJECT_BINARY_DIR}/cmake)

set(deskOrders_SRCs
    main.cpp
    
)

add_executable(deskOrders ${deskOrders_SRCs})
target_link_libraries(deskOrders deskResources deskCore Qt5::Widgets Qt5::Qml)
