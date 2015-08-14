option (QBU_BUILD_DATABASE 				"Build Database Support" ON)
option (QBU_BUILD_LOG 					"Build Log Support" ON)
option (QBU_BUILD_WIDGETS				"Build Widgets Support" OFF)

if (QBU_BUILD_LOG)
	conditional_define(QBU_BUILD_LOG QBU_HAS_LOG)
	set(QXT_FIND_COMPONENTS QxtCore, QxtGui)
	set(QXT_USE_QXTCORE TRUE)
	find_package(Qxt REQUIRED)
	include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/GetQxtRuntime.cmake)
endif()

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
set (${PROJECT_NAME}_DEFINES ${${PROJECT_NAME}_DEFINES} PARENT_SCOPE)
