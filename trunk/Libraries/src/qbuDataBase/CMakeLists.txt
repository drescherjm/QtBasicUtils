myproject(qbuDataBase)

CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)

OPTION(USE_BIND_FOR_INSERT "Use Qt databinding for insert queries" ON)

FIND_PACKAGE( Qt4 REQUIRED )
set(QT_USE_QTXML true)
set(QT_USE_QTSQL true)
INCLUDE( ${QT_USE_FILE} )

if(USE_BIND_FOR_INSERT)
ADD_DEFINITIONS(-DUSE_BIND_FOR_INSERT)
ENDIF(USE_BIND_FOR_INSERT)

#set(Boost_ADDITIONAL_VERSIONS "1.47" "1.47.0" "1.48" "1.48.0")
FIND_PACKAGE( Boost REQUIRED )

set (${LOCAL_PROJECT_NAME}_VERSION_MAJOR 1)
set (${LOCAL_PROJECT_NAME}_VERSION_MINOR 0)

set (${LOCAL_PROJECT_NAME}_INSTALL_INCLUDE  ${CMAKE_INSTALL_PREFIX}/Include )
set (${LOCAL_PROJECT_NAME}_INSTALL_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (${LOCAL_PROJECT_NAME}_INSTALL_RELEASE_LIB ${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_INSTALL_DEBUG_LIB ${LOCAL_PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

set (${LOCAL_PROJECT_NAME}_TREE_INCLUDE  ${${PROJECT_NAME}_INCLUDE_DIRS}/${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_TREE_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set (${LOCAL_PROJECT_NAME}_TREE_RELEASE_LIB ${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_TREE_DEBUG_LIB ${LOCAL_PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

SET( ${LOCAL_PROJECT_NAME}_SRCS
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
	./src/qbuPropertyMap.cxx
	./src/qbuStringList.cxx
	./src/qbuException.cxx
)

SET( ${LOCAL_PROJECT_NAME}_EXT_HDRS 
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDatabaseMacros.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDatabase.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBTransaction.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBSavePoint.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuSelectQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuCreateTableQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuCreateViewQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuTable.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBColumnDef.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBColumnDefList.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuTableSchema.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDatabaseFunctions.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuInsertQuery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBConstants.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuDBMacros.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuPropertyMap.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuStringList.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuException.h
)

SET( ${LOCAL_PROJECT_NAME}_MOC_HDRS 
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuInfo.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuTableColumnDef.h
)

# some .ui files
SET( ${LOCAL_PROJECT_NAME}_UIS
)

# and finally an resource file
SET( ${LOCAL_PROJECT_NAME}_RCS
)

SET( ${LOCAL_PROJECT_NAME}_INT_HDRS

)

#Add precompiled header support
MSVC_PCH_SUPPORT(${LOCAL_PROJECT_NAME})

# this command will generate rules that will run rcc on all files from UPMC_LA_RCS
# in result UPMC_LA_RC_SRCS variable will contain paths to files produced by rcc
QT4_ADD_RESOURCES( ${LOCAL_PROJECT_NAME}_RC_SRCS ${${LOCAL_PROJECT_NAME}_RCS} )

# and finally this will run moc:
QT4_WRAP_CPP( ${LOCAL_PROJECT_NAME}_MOC_SRCS ${${LOCAL_PROJECT_NAME}_MOC_HDRS} )

# this will run uic on .ui files:
QT4_WRAP_UI( ${LOCAL_PROJECT_NAME}_UI_HDRS ${${LOCAL_PROJECT_NAME}_UIS} )

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

install (FILES
	${PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}Config.cmake
	${PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}LibraryDepends.cmake
	${PROJECT_SOURCE_DIR}/${LOCAL_PROJECT_NAME}Use.cmake
	DESTINATION lib
)

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES FOLDER Libraries)

install (TARGETS ${LOCAL_PROJECT_NAME} DESTINATION lib)
install (FILES ${${LOCAL_PROJECT_NAME}_EXT_HDRS} ${${LOCAL_PROJECT_NAME}_MOC_HDRS} DESTINATION include)


