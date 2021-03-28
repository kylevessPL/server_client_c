cmake_minimum_required(VERSION 3.17)
project(server_client C)

set(CMAKE_C_STANDARD 99)

set(SERVER_DIR server)
set(CLIENT_DIR client)
set(COMMON_DIR common)

add_subdirectory(${SERVER_DIR})
add_subdirectory(${CLIENT_DIR})
add_subdirectory(${COMMON_DIR})