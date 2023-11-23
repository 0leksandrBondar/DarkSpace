cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
        main.cpp
        client.cpp
        Gui/qml_resource.qrc
        Gui/LoginPage/loginPageResource.qrc
)

set(HEADERS
        client.h)

include(IconMaker.cmake)
add_icon()

add_executable(${PROJECT_NAME} ${APP_TYPE} ${SOURCES} ${APP_ICON} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt
        ClientData
)