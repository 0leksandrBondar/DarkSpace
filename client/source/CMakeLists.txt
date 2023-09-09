cmake_minimum_required(VERSION 3.5)

set(SOURCES
        main.cpp
        icons.qrc
        client.cpp
        Gui/qml_resource.qrc
        Gui/LoginPage/loginPageResource.qrc)

set(HEADERS
        client.h)

#add_library(Client ${HEADERS} ${SOURCES})


find_package(Qt6 COMPONENTS Core Quick Network QuickControls2 REQUIRED)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt6::Core
        Qt6::Network
        Qt6::Quick
        ClientData
)