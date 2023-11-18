cmake_minimum_required(VERSION 3.5)

include(cmake/deploy.cmake)

project(DarkSpace VERSION 0.1 LANGUAGES CXX)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(general-lib)
