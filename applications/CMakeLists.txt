
file(GLOB_RECURSE ProtoFiles "${PROJECT_SOURCE_DIR}/protos/config/*.proto")

protobuf_generate_cpp(ProtobufSources ProtobufHeaders ${ProtoFiles})
grpc_generate_cpp(ProtobufGRPCSources ProtobufGRPCHeaders ${ProtoFiles})

add_executable(front-delivery main.cpp ${ProtobufSources} ${ProtobufGRPCSources})
target_link_libraries(front-delivery grpc++ grpc++_reflection)

target_include_directories(front-delivery PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR}/cmake)
