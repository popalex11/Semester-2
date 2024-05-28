cmake_minimum_required(VERSION 3.14)

project(MyQtApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MyQtApp main.cpp)

target_link_libraries(MyQtApp PRIVATE Qt5::Widgets)
