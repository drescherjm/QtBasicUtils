PROJECT(qbuDataBase)

CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)

OPTION(USE_BIND_FOR_INSERT "Use Qt databinding for insert queries" ON)

FIND_PACKAGE( Qt4 REQUIRED )
set(QT_USE_QTXML true)
set(QT_USE_QTSQL true)
INCLUDE( ${QT_USE_FILE} )

if(USE_BIND_FOR_INSERT)
ADD_DEFINITIONS(-DUSE_BIND_FOR_INSERT)
ENDIF(USE_BIND_FOR_INSERT)

set(Boost_ADDITIONAL_VERSIONS "1.47" "1.47.0" "1.48" "1.48.0")
FIND_PACKAGE( Boost REQUIRED )

set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 0)

set (${PROJECT_NAME}_INSTALL_INCLUDE  ${CMAKE_INSTALL_PREFIX}/Include )
set (${PROJECT_NAME}_INSTALL_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (${PROJECT_NAME}_INSTALL_RELEASE_LIB ${PROJECT_NAME} )
set (${PROJECT_NAME}_INSTALL_DEBUG_LIB ${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

set (${PROJECT_NAME}_TREE_INCLUDE  ${CMAKE_CURRENT_SOURCE_DIR}/Include )
set (${PROJECT_NAME}_TREE_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set (${PROJECT_NAME}_TREE_RELEASE_LIB ${PROJECT_NAME} )
set (${PROJECT_NAME}_TREE_DEBUG_LIB ${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

#configure_file (
#	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
#	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
#)

SET( ${PROJECT_NAME}_SRCS
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
)

SET( ${PROJECT_NAME}_EXT_HDRS 
	./Include/qbuDatabaseMacros.h
	./Include/qbuDatabase.h
	./Include/qbuDBTransaction.h
	./Include/qbuDBSavePoint.h
	./Include/qbuQuery.h
	./Include/qbuSelectQuery.h
	./Include/qbuCreateTableQuery.h
	./Include/qbuCreateViewQuery.h
	./Include/qbuTable.h
	./Include/qbuDBColumnDef.h
	./Include/qbuDBColumnDefList.h
	./Include/qbuTableSchema.h
	./Include/qbuDatabaseFunctions.h
	./Include/qbuInsertQuery.h
	./Include/qbuDBConstants.h
	./Include/qbuDBMacros.h
)

SET( ${PROJECT_NAME}_MOC_HDRS 
	./Include/qbuInfo.h
	./Include/qbuTableColumnDef.h
)

# some .ui files
SET( ${PROJECT_NAME}_UIS
)

# and finally an resource file
SET( ${PROJECT_NAME}_RCS
)

SET( ${PROJECT_NAME}_INT_HDRS

)

#Add precompiled header support
MSVC_PCH_SUPPORT(${PROJECT_NAME})

# this command will generate rules that will run rcc on all files from UPMC_LA_RCS
# in result UPMC_LA_RC_SRCS variable will contain paths to files produced by rcc
QT4_ADD_RESOURCES( ${PROJECT_NAME}_RC_SRCS ${${PROJECT_NAME}_RCS} )

# and finally this will run moc:
QT4_WRAP_CPP( ${PROJECT_NAME}_MOC_SRCS ${${PROJECT_NAME}_MOC_HDRS} )

# this will run uic on .ui files:
QT4_WRAP_UI( ${PROJECT_NAME}_UI_HDRS ${${PROJECT_NAME}_UIS} )

SOURCE_GROUP("Generated" FILES
	  ${${PROJECT_NAME}_RC_SRCS}
	  ${${PROJECT_NAME}_MOC_SRCS}
	  ${${PROJECT_NAME}_UI_HDRS}
)

SOURCE_GROUP("Resources" FILES
	  ${${PROJECT_NAME}_UIS}
	  ${${PROJECT_NAME}_RCS}
)

IF(BUILD_DOCUMENTATION)

ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR})
ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/src)
ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/Include)

ENDIF(BUILD_DOCUMENTATION)

include_directories( 
	${PROJECT_BINARY_DIR} 
	${PROJECT_BINARY_DIR}/.. 
	${PROJECT_SOURCE_DIR}/Include
	${STUDY_MANAGER_SRC}/Include
)

add_library(${PROJECT_NAME} 
	${${PROJECT_NAME}_SRCS} 
	${${PROJECT_NAME}_EXT_HDRS} 
	${${PROJECT_NAME}_MOC_HDRS}
	${${PROJECT_NAME}_MOC_SRCS} 
	${${PROJECT_NAME}_INT_HDRS} 
	${${PROJECT_NAME}_UI_HDRS}
	${${PROJECT_NAME}_RC_SRCS}
)

install (FILES
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}LibraryDepends.cmake
	${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Use.cmake
	DESTINATION lib
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Libraries)

install (TARGETS ${PROJECT_NAME} DESTINATION lib)
install (FILES ${${PROJECT_NAME}_EXT_HDRS} ${${PROJECT_NAME}_MOC_HDRS} DESTINATION include)


