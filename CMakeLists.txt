cmake_minimum_required(VERSION 3.6)
project(CatchUp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/TreeEntry.cpp src/TreeEntry.h src/Date.cpp src/Date.h src/TreeBuilder.cpp src/TreeBuilder.h)
add_executable(CatchUp ${SOURCE_FILES})