option (QBU_BUILD_DATABASE 				"Build Database Support" ON)
option (QBU_BUILD_LOG 					"Build Log Support" ON)
option (QBU_BUILD_WIDGETS				"Build Widgets Support" OFF)

add_subdirectory(qbuBase)
add_subdirectory(qbuCmdLine)

if(QBU_BUILD_DATABASE)
	add_subdirectory(qbuDataBase)
endif(QBU_BUILD_DATABASE)

if(QBU_BUILD_LOG)
	add_subdirectory(qbuLog)
endif(QBU_BUILD_LOG)

if(QBU_BUILD_WIDGETS)
	add_subdirectory(qbuWidgets)
endif(QBU_BUILD_WIDGETS)

set (${PROJECT_NAME}_LIBRARIES ${${PROJECT_NAME}_LIBRARIES} PARENT_SCOPE)
