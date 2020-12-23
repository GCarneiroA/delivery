
# Generate table files
file(GLOB_RECURSE ddlFiles "${PROJECT_SOURCE_DIR}/ddl/*.sql")
sqlpp_generate_table(tableHeaders "basic" ${ddlFiles})

# Generate grpc files
file(GLOB_RECURSE userProtoFiles "${PROJECT_SOURCE_DIR}/protos/user/*.proto")
protobuf_generate_cpp(userProtoSources userProtoHeaders ${userProtoFiles})
grpc_generate_cpp(userProtoGRPCSources userProtoGRPCHeaders ${userProtoFiles})

add_library(userServiceModules)
target_link_libraries(userServiceModules gRPC::grpc++ gRPC::grpc++_reflection sqlpp11::mysql)
target_sources(userServiceModules PRIVATE
    userCall.cpp
    ${tableHeaders}
    ${userProtoSources}
    ${userProtoGRPCSources}
)
target_include_directories(userServiceModules PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR})

