
set(ServiceConfigModules_SRCs
    ServiceSignatureCall.cpp
    ServiceVersionCall.cpp
    ServiceLoginCall.cpp
)

file(GLOB_RECURSE ProtoFiles "${PROJECT_SOURCE_DIR}/protos/config/*.proto")
    protobuf_generate_cpp(ProtobufSources ProtobufHeaders ${ProtoFiles})
    grpc_generate_cpp(ProtobufGRPCSources ProtobufGRPCHeaders ${ProtoFiles})

add_library(serviceConfigModules ${ServiceConfigModules_SRCs} ${ProtobufSources} ${ProtobufGRPCSources})
target_link_libraries(serviceConfigModules grpc++ grpc++_reflection)

target_include_directories(serviceConfigModules PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR}/cmake)

