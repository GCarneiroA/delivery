
# Generate table files
file(GLOB_RECURSE ddlFiles "${PROJECT_SOURCE_DIR}/ddl/*.sql")
sqlpp_generate_table(tableHeaders "basic" ${ddlFiles})

# Generate grpc files
file(GLOB_RECURSE userProtoFiles "${PROJECT_SOURCE_DIR}/protos/user/*.proto")
protobuf_generate_cpp(userProtoSources userProtoHeaders ${userProtoFiles})
grpc_generate_cpp(userProtoGRPCSources userProtoGRPCHeaders ${userProtoFiles})

add_executable(userService)
target_link_libraries(userService gRPC::grpc++ gRPC::grpc++_reflection sqlpp11::mysql)

target_include_directories(userService PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR})

target_sources(userService PRIVATE
    main.cpp
    userCall.cpp
    serviceConnect.cpp
    ${tableHeaders}
    ${userProtoSources}
    ${userProtoGRPCSources}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
