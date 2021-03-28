cmake_minimum_required(VERSION 3.17)
project(server_client C)

set(CMAKE_C_STANDARD 99)

add_library(common_lib src/endianness.c src/protocol.c)
target_include_directories(common_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
