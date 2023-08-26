cmake_minimum_required(VERSION 3.5)

set(SOURCES
        client.cpp
        Gui/qml_resource.qrc
        Gui/LoginPage/loginPageResource.qrc)

set(HEADERS
        client.h)

add_library(Client ${HEADERS} ${SOURCES})

target_include_directories(Client PUBLIC ./)

find_package(Qt6 COMPONENTS Core Quick Network QuickControls2 REQUIRED)

target_link_libraries(Client
        PUBLIC
        Qt6::Core
        Qt6::Network
        Qt6::Quick
        ClientData
)

qt6_add_resources(RESOURCES Gui/qml_resource.qrc)
target_sources(Client PUBLIC ${RESOURCES})
