cmake_minimum_required(VERSION 3.6)
project(CatchUp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp TreeEntry.cpp TreeEntry.h Date.cpp Date.h TreeBuilder.cpp TreeBuilder.h)
add_executable(CatchUp ${SOURCE_FILES})