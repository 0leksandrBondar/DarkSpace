cmake_minimum_required(VERSION 3.5)

project(DarkSpace VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(source/program)
add_subdirectory(source/Client)
