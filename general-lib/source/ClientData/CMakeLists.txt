cmake_minimum_required(VERSION 3.14)

set(SOURCE
        clientdata.cpp)

set(HEADERS
        clientdata.h
        )

add_library(ClientData ${SOURCES} ${HEADERS}
        clientdata.cpp)

target_link_libraries(ClientData
        Qt
)

target_include_directories(ClientData PUBLIC ./)
