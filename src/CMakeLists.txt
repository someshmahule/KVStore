cmake_minimum_required(VERSION 3.16)

project(Tcp-learnings)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(server
    network/server/server.cpp
    protocol/parser.cpp
    db/kvstore.cpp
)

add_executable(client network/client/client.cpp)