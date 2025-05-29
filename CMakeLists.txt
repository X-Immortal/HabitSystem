cmake_minimum_required(VERSION 3.29)
project(HabitSystem)

set(CMAKE_CXX_STANDARD 20)

# 在""中填入你电脑上的Qt安装目录
if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # 我的Mac
    set(CMAKE_PREFIX_PATH "/Users/Apple/Qt/6.9.0/macos/lib/cmake")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # 我的Windows
    set(CMAKE_CXX_COMPILER "E:\\software\\Qt\\Tools\\mingw1310_64\\bin\\g++.exe")
    set(CMAKE_PREFIX_PATH "E:\\software\\Qt\\6.9.0\\mingw_64\\lib\\cmake")
endif ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

file(GLOB SOURCES "ui/*.cpp" "ui/*.h" "data/*.cpp" "tools/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets)

