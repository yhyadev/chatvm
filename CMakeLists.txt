cmake_minimum_required(VERSION 3.27)

project(ChatVM)

set(CMAKE_CXX_STANDARD 23)

add_executable(chatvm src/main.cpp src/vm.cpp src/chunk.cpp)
