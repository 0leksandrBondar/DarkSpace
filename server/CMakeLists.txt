cmake_minimum_required(VERSION 3.5)

project(DarkSpaceServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(source/DBManager)
add_subdirectory(source/Program)
add_subdirectory(source/Server)
