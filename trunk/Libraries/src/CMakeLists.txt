CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

option (QBU_BUILD_DATABASE 				"Build Database Support" OFF)
option (QBU_BUILD_LOG 					"Build Log Support" ON)

add_subdirectory(qbuBase)
add_subdirectory(qbuCmdLine)

if(QBU_BUILD_DATABASE)
	add_subdirectory(qbuDataBase)
endif(QBU_BUILD_DATABASE)

if(QBU_BUILD_LOG)
	add_subdirectory(qbuLog)
endif(QBU_BUILD_LOG)

set (${PROJECT_NAME}_LIBRARIES ${${PROJECT_NAME}_LIBRARIES} PARENT_SCOPE)
