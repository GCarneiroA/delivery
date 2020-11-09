
FetchContent_GetProperties(mysqlpp)
if (NOT mysqlpp_POPULATED)
    FetchContent_Populate(mysqlpp)
    add_subdirectory(${mysqlpp_SOURCE_DIR} ${mysqlpp_BINARY_DIR})
endif()
