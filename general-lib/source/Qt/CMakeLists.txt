cmake_minimum_required(VERSION 3.14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Quick Network Sql REQUIRED)

add_library(Qt INTERFACE)

target_link_libraries(Qt INTERFACE
        Qt6::Core
        Qt6::Network
        Qt6::Quick
        Qt6::Sql
)