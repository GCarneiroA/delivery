
set(deskResources_SRCs
    wrappers/LoginWrapper.cpp

)

qt5_add_resources(RESOURCES resources.qrc)

add_library(deskResources SHARED ${deskResources_SRCs} ${RESOURCES})
target_link_libraries(deskResources deskCore Qt5::Qml)

target_include_directories(deskResources
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
