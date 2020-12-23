
include(FetchContent)

FetchContent_Declare(mysqlpp
    GIT_REPOSITORY  https://github.com/GCarneiroA/sqlpp11-connector-mysql.git
    GIT_TAG         origin/dependencies
)
add_subdirectory(mysqlpp)
