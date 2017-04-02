cmake_minimum_required(VERSION 3.6)
project(CatchUp)

set(CMAKE_CXX_STANDARD 11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set (CMAKE_PREFIX_PATH "C:\\QT\\5.8\\mingw53_32\\")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

set(SOURCE_FILES src/main.cpp src/TreeEntry.cpp src/TreeEntry.h src/Date.cpp src/Date.h src/TreeBuilder.cpp src/TreeBuilder.h src/TreeFilterer.cpp src/TreeFilterer.h src/mainwindow.cpp src/mainwindow.h)
add_executable(CatchUp ${SOURCE_FILES})

target_link_libraries(CatchUp Qt5::Widgets Qt5::Gui Qt5::Core)