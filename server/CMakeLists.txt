cmake_minimum_required(VERSION 3.17)
project(server_client C)

set(CMAKE_C_STANDARD 99)

add_executable(server src/server.c)

add_library(server_lib src/client_handler.c)

target_include_directories(server_lib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(server_lib common_lib)
target_link_libraries(server server_lib)
