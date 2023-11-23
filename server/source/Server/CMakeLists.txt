add_library(Server server.cpp)

target_link_libraries(Server
    PUBLIC
    Qt
    ClientData
    Db-Manager
)

target_include_directories(Server PUBLIC ./)
