
# Auto generate grpc files
file(GLOB_RECURSE ProtoFiles "${PROJECT_SOURCE_DIR}/protos/config/*.proto")
protobuf_generate_cpp(ProtobufSources ProtobufHeaders ${ProtoFiles})
grpc_generate_cpp(ProtobufGRPCSources ProtobufGRPCHeaders ${ProtoFiles})

set(deskCore_SRCs
    ${ProtobufSources}
    ${ProtobufGRPCSources}
    ClientConnection.cpp
)

add_library(deskCore SHARED ${deskCore_SRCs})
target_link_libraries(deskCore grpc++ grpc++_reflection Qt5::Core)

target_include_directories(deskCore
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
            ${PROJECT_BINARY_DIR}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
