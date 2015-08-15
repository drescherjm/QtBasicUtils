myproject(qbuDataBase)

option(USE_BIND_FOR_INSERT "Use Qt databinding for insert queries" ON)
option(USE_EXCEPTIONS "Use exceptions" ON)

conditional_define(USE_EXCEPTIONS QBU_HAVE_EXCEPTIONS)

if (USE_EXCEPTIONS)
	set (${LOCAL_PROJECT_NAME}_DEFINES -DQBU_HAVE_EXCEPTIONS)
endif()

set(QXT_FIND_COMPONENTS QxtCore, QxtGui)
set(QXT_USE_QXTCORE TRUE)
find_package(Qxt REQUIRED)
include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/GetQxtRuntime.cmake)

if(${PROJECT_NAME}_QT_VERSION VERSION_GREATER "4")

	set (QT_LIBRARIES Qt5::Widgets Qt5::WinMain Qt5::Xml)
	set (QT_MODULES Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WinMain Qt5::Xml Qt5::Sql)
	
	find_qt5_packages()
	
else(${PROJECT_NAME}_QT_VERSION VERSION_GREATER "4")
	set(QT_USE_QTXML true)
	set(QT_USE_QTSQL true)
	find_package(Qt4 REQUIRED)
	include(${QT_USE_FILE})
endif(${PROJECT_NAME}_QT_VERSION VERSION_GREATER "4")

if(USE_BIND_FOR_INSERT)
	add_definitions(-DUSE_BIND_FOR_INSERT)
ENDIF(USE_BIND_FOR_INSERT)

#set(Boost_ADDITIONAL_VERSIONS "1.47" "1.47.0" "1.48" "1.48.0")
find_package( Boost REQUIRED )

include_directories( ${Boost_INCLUDE_DIRS} )

# set (${LOCAL_PROJECT_NAME}_VERSION_MAJOR 1)
# set (${LOCAL_PROJECT_NAME}_VERSION_MINOR 0)

set (${LOCAL_PROJECT_NAME}_INSTALL_INCLUDE  ${CMAKE_INSTALL_PREFIX}/Include )
set (${LOCAL_PROJECT_NAME}_INSTALL_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (${LOCAL_PROJECT_NAME}_INSTALL_RELEASE_LIB ${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_INSTALL_DEBUG_LIB ${LOCAL_PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

set (${LOCAL_PROJECT_NAME}_TREE_INCLUDE  ${${PROJECT_NAME}_SRC_INCLUDE_DIR}/${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_TREE_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set (${LOCAL_PROJECT_NAME}_TREE_RELEASE_LIB ${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_TREE_DEBUG_LIB ${LOCAL_PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

set( ${LOCAL_PROJECT_NAME}_SRCS
	./src/qbuDatabase.cxx
	./src/qbuDBTransaction.cxx
	./src/qbuDBSavePoint.cxx
	./src/qbuQuery.cxx
	./src/qbuSelectQuery.cxx
	./src/qbuCreateTableQuery.cxx
	./src/qbuCreateViewQuery.cxx
	./src/qbuTable.cxx
	./src/qbuInfo.cxx
	./src/qbuDBColumnDef.cxx
	./src/qbuDBColumnDefList.cxx
	./src/qbuTableColumnDef.cxx
	./src/qbuTableSchema.cxx
	./src/qbuDatabaseFunctions.cxx
	./src/qbuInsertQuery.cxx
	./src/qbuDBSettingsTableBase.cxx
	./src/qbuDBSettingInfo.cxx
	./src/qbuSimpleQuery.cxx
	./src/qbuDBExpression.cxx
	./src/qbuDBJoin.cxx
	./src/qbuDeleteQuery.cxx
	./src/qbuDBView.cxx
)

set( ${LOCAL_PROJECT_NAME}_EXT_HDRS 
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDatabaseMacros.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDatabase.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBTransaction.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBSavePoint.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuSelectQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuCreateTableQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuCreateViewQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuTable.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBColumnDefList.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuTableSchema.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDatabaseFunctions.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuInsertQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBConstants.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBMacros.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBSettingsTableBase.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBSettingInfo.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuSimpleQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBExpression.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBJoin.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDeleteQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBView.h
)

set( ${LOCAL_PROJECT_NAME}_MOC_HDRS 
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuInfo.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuTableColumnDef.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBColumnDef.h
)

# some .ui files
set( ${LOCAL_PROJECT_NAME}_UIS
)

# and finally an resource file
set( ${LOCAL_PROJECT_NAME}_RCS
)

set( ${LOCAL_PROJECT_NAME}_INT_HDRS

)

#Add precompiled header support
MSVC_PCH_SUPPORT(${LOCAL_PROJECT_NAME})

# this command will generate rules that will run rcc on all files from UPMC_LA_RCS
# in result UPMC_LA_RC_SRCS variable will contain paths to files produced by rcc
QT45_ADD_RESOURCES( ${LOCAL_PROJECT_NAME}_RC_SRCS ${${LOCAL_PROJECT_NAME}_RCS} )

# and finally this will run moc:
QT45_WRAP_CPP( ${LOCAL_PROJECT_NAME}_MOC_SRCS ${${LOCAL_PROJECT_NAME}_MOC_HDRS} )

# this will run uic on .ui files:
QT45_WRAP_UI( ${LOCAL_PROJECT_NAME}_UI_HDRS ${${LOCAL_PROJECT_NAME}_UIS} )

SOURCE_GROUP("Generated" FILES
	  ${${LOCAL_PROJECT_NAME}_RC_SRCS}
	  ${${LOCAL_PROJECT_NAME}_MOC_SRCS}
	  ${${LOCAL_PROJECT_NAME}_UI_HDRS}
)

SOURCE_GROUP("Resources" FILES
	  ${${LOCAL_PROJECT_NAME}_UIS}
	  ${${LOCAL_PROJECT_NAME}_RCS}
)

IF(BUILD_DOCUMENTATION)

	ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR})
	ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/src)
	ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/Include)

ENDIF(BUILD_DOCUMENTATION)


include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${PROJECT_BINARY_DIR} 
	${PROJECT_BINARY_DIR}/.. 
	${${PROJECT_NAME}_INCLUDE_DIRS}
)

add_library(${LOCAL_PROJECT_NAME} 
	${${LOCAL_PROJECT_NAME}_SRCS} 
	${${LOCAL_PROJECT_NAME}_EXT_HDRS} 
	${${LOCAL_PROJECT_NAME}_MOC_HDRS}
	${${LOCAL_PROJECT_NAME}_MOC_SRCS} 
	${${LOCAL_PROJECT_NAME}_INT_HDRS} 
	${${LOCAL_PROJECT_NAME}_UI_HDRS}
	${${LOCAL_PROJECT_NAME}_RC_SRCS}
)

#########################################################################################

if (BUILD_${LOCAL_PROJECT_NAME}_SHARED)
	TARGET_LINK_LIBRARIES ( 
		${LOCAL_PROJECT_NAME} 
		${UPMC_EXTERNAL_LIBS} 
		${QT_LIBRARIES} 
		${QXT_LIBRARIES}
	)

	install(TARGETS ${LOCAL_PROJECT_NAME}
	   RUNTIME
	   DESTINATION bin
	   COMPONENT Applications
	)

endif(BUILD_${LOCAL_PROJECT_NAME}_SHARED)

#########################################################################################

GENERATE_EXPORT_HEADER( ${LOCAL_PROJECT_NAME} 
	BASE_NAME ${LOCAL_PROJECT_NAME}
	EXPORT_MACRO_NAME ${LOCAL_PROJECT_NAME}_EXPORT
	EXPORT_FILE_NAME "${LOCAL_PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}LibraryDefines.h"
	STATIC_DEFINE ${LOCAL_PROJECT_NAME}_STATIC
)

#########################################################################################

install (FILES
	${PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}Config.cmake
	${PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}LibraryDepends.cmake
	${PROJECT_SOURCE_DIR}/${LOCAL_PROJECT_NAME}Use.cmake
	DESTINATION lib
)

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES FOLDER Libraries)

install (TARGETS ${LOCAL_PROJECT_NAME} DESTINATION lib)
install (FILES ${${LOCAL_PROJECT_NAME}_EXT_HDRS} ${${LOCAL_PROJECT_NAME}_MOC_HDRS} DESTINATION include)

set (${PROJECT_NAME}_LIBRARIES ${${PROJECT_NAME}_LIBRARIES} ${LOCAL_PROJECT_NAME} PARENT_SCOPE)
set (${PROJECT_NAME}_DEFINES ${${PROJECT_NAME}_DEFINES} ${${LOCAL_PROJECT_NAME}_DEFINES} PARENT_SCOPE)


