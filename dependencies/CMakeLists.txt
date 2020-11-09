
include(FetchContent)

option(USE_SYSTEM_GRPC "Use system installed gRPC" OFF)
if (USE_SYSTEM_GRPC)
    find_package(gRPC CONFIG REQUIRED)
else()
    FetchContent_Declare(gRPC
        GIT_REPOSITORY  https://github.com/grpc/grpc
        GIT_TAG         v1.33.2
    )
    add_subdirectory(gRPC)
endif()

