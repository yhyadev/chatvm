cmake_minimum_required(VERSION 3.27)

project(ChatVM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable(chatvm src/main.cpp src/vm.cpp src/chunk.cpp src/value.cpp)
