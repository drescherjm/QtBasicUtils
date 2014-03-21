CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

option (QBU_BUILD_DATABASE 				"Build Database Support" OFF)

add_subdirectory(qbuBase)
add_subdirectory(qbuCmdLine)

if(QBU_BUILD_DATABASE)
	add_subdirectory(qbuDataBase)
endif(QBU_BUILD_DATABASE)
