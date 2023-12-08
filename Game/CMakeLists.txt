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
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5WebSockets REQUIRED)

add_executable(Game main.cpp MainWindow.cpp MainWindow.h
        level.cpp
        websockethandler.cpp
        messageprocesshandler.cpp
        gameitem.cpp
        enemy.cpp
        gamemanager.cpp
        obstacles.cpp
        startmenu.cpp
        startmenu.cpp
        midmenu.h
        midmenu.cpp
        multiplayermainwindow.h
        multiplayermainwindow.cpp)

target_link_libraries(Game Qt5::Core)
target_link_libraries(Game Qt5::Widgets)
target_link_libraries(Game Qt5::Quick)
target_link_libraries(Game Qt5::Multimedia)
target_link_libraries(Game Qt5::WebSockets)