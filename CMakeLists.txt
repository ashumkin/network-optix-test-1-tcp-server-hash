cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(server)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib-cache
        CACHE PATH
        "Single Directory for all"
    )

enable_testing()

include_directories(include lib/asio/asio/include lib/hash-library)
IF (WIN32)
    include_directories(lib\\boost_1_60_0 lib\\boost_1_60_0\\boost\\predef\\other)
ENDIF()

add_subdirectory(src build/src)
add_subdirectory(test build/test)
