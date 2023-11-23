add_library(Db-Manager dbmanager.cpp)

target_link_libraries(Db-Manager
    PUBLIC
    Qt
    ClientData
)

target_include_directories(Db-Manager PUBLIC ./)
