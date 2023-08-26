add_library(Db-Manager dbmanager.cpp)

find_package(Qt6 COMPONENTS Core Network Sql REQUIRED)

target_link_libraries(Db-Manager
    PUBLIC
    Qt6::Core
    Qt6::Network
    Qt::Sql
    ClientData
)

target_include_directories(Db-Manager PUBLIC ./)
