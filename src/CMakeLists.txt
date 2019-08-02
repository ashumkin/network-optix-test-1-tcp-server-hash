project(server)

add_library(sha256 ../lib/hash-library/sha256.cpp)

add_library(sha256calc SHARED ../sha256calc/sha256calculator.cpp)

add_executable(server
    server.cpp
)

target_link_libraries(sha256calc sha256)
target_link_libraries(server sha256calc)
IF (WIN32)
    target_link_libraries(server ws2_32 wsock32)
ELSE()
    target_link_libraries(server pthread)
ENDIF()
