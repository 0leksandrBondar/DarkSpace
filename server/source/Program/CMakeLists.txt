add_executable(ServerProgram main.cpp)

target_link_libraries(ServerProgram PUBLIC
	Db-Manager
	Message-Data
	Server
)
