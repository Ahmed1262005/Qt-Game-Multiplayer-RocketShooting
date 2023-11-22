cmake_minimum_required(VERSION 3.10)
project(Game)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:\\Qt\\6.5.2\\mingw_64\\")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

add_executable(Game main.cpp MainWindow.cpp MainWindow.h )

target_link_libraries(Game Qt5::Core)
target_link_libraries(Game Qt5::Widgets)
target_link_libraries(Game Qt5::Quick)
