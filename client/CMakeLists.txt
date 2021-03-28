cmake_minimum_required(VERSION 3.17)
project(server_client C)

set(CMAKE_C_STANDARD 99)

add_executable(client src/client.c)
target_link_libraries(client common_lib)
