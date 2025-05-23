cmake_minimum_required(VERSION 3.29)
project(HabitSystem)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_COMPILER "E:\\software\\Qt\\Tools\\mingw1310_64\\bin\\g++.exe")
set(CMAKE_PREFIX_PATH "E:\\software\\Qt\\6.9.0\\mingw_64\\lib\\cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

file(GLOB SOURCES "ui\\*.cpp" "ui\\*.h")

add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets)

