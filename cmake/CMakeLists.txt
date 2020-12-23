
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)

function(GRPC_GENERATE_CPP SRCS HDRS)
    if(NOT ARGN)
        message(SEND_ERROR "Error: GRPC_GENERATE_CPP() called without any proto files")
        return()
    endif()

    foreach(FIL ${ARGN})
        get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
        get_filename_component(ABS_PATH ${ABS_FIL} DIRECTORY)

        list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
        if(${_contains_already} EQUAL -1)
            list(APPEND _protobuf_include_path ${ABS_PATH})
        endif()
    endforeach()

    if(DEFINED PROTOBUF_IMPORT_DIRS)
        foreach(DIR ${PROTOBUF_IMPORT_DIRS})
        get_filename_component(ABS_PATH ${DIR} ABSOLUTE)
        list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
        if(${_contains_already} EQUAL -1)
            list(APPEND _protobuf_include_path ${ABS_PATH})
        endif()
        endforeach()
    endif()

    set(${SRCS})
    set(${HDRS})

    foreach(FIL ${ARGN})
        get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
        get_filename_component(FIL_WE ${FIL} NAME_WE)
        
        list(APPEND ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.cc")
        list(APPEND ${HDRS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.h")

        add_custom_command(
            OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.cc"
                    "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.grpc.pb.h"
            COMMAND
                ${Protobuf_PROTOC_EXECUTABLE}
            ARGS
                -I ${_protobuf_include_path}
                --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
                --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
                ${ABS_FIL}
            DEPENDS
                ${ABS_FIL} ${Protobuf_PROTOC_EXECUTABLE}
            COMMENT "Running C++ gRPC compiler on ${FIL}"
            VERBATIM)
    endforeach()

    set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
    set(${SRCS} ${${SRCS}} PARENT_SCOPE)
    set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()
