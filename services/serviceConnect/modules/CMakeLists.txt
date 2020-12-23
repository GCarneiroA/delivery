
file(GLOB_RECURSE ProtoFiles "${PROJECT_SOURCE_DIR}/protos/config/*.proto")
    protobuf_generate_cpp(ProtobufSources ProtobufHeaders ${ProtoFiles})
    grpc_generate_cpp(ProtobufGRPCSources ProtobufGRPCHeaders ${ProtoFiles})

add_library(serviceConnectModules)
target_link_libraries(serviceConnectModules gRPC::grpc++ gRPC::grpc++_reflection)
target_sources(serviceConnectModules PRIVATE
    ServiceSignatureCall.cpp
    ServiceVersionCall.cpp
    ServiceLoginCall.cpp
    ${ProtobufSources}
    ${ProtobufGRPCSources}
)
target_include_directories(serviceConnectModules PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR})

