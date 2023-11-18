cmake_minimum_required(VERSION 3.14)

add_custom_target(MakeDeploy
        #TODO : remove the hardCode -  C:/Qt/6.6.0/msvc2019_64/bin/windeployqt6.exe
COMMAND C:/Qt/6.6.0/msvc2019_64/bin/windeployqt6.exe --qmldir ${CMAKE_SOURCE_DIR}/client/source/Gui ${CMAKE_BINARY_DIR}/client/source/DarkSpace.exe
COMMAND C:/Qt/6.6.0/msvc2019_64/bin/windeployqt6.exe ${CMAKE_BINARY_DIR}/server/source/Program/ServerProgram.exe
)