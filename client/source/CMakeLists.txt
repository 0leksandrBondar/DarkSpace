cmake_minimum_required(VERSION 3.5)

set(SOURCES
        main.cpp
        icons.qrc
        client.cpp
        Gui/qml_resource.qrc
        Gui/LoginPage/loginPageResource.qrc
)

set(HEADERS
        client.h)

find_package(Qt6 COMPONENTS Core Quick Network QuickControls2 REQUIRED)

include(IconMaker.cmake)
add_icon()

add_executable(${PROJECT_NAME} ${APP_TYPE} ${SOURCES} ${APP_ICON} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt6::Core
        Qt6::Network
        Qt6::Quick
        ClientData
)