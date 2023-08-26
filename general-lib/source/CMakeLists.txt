set(SOURCE
        ClientData/clientdata.cpp
)

set(HEADERS
        ClientData/clientdata.cpp)

add_library(ClientData ${SOURCES} ${HEADERS})

target_include_directories(ClientData PUBLIC ./)

find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(ClientData
        PUBLIC
        Qt6::Core
)


