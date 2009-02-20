PROJECT(QtBasicUtils)

CMAKE_MINIMUM_REQUIRED (VERSION 2.6 FATAL_ERROR)

option (BUILD_TESTING "Build Tests" ON)
option (BUILD_EXPERIMENTAL "Build Experimental Code" ON)

SET (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug;Release" FORCE)

IF(WIN32)

#The following command changes \ to / in the Program Files Path so CMake will not complain
#about bad escape sequences.
string (REPLACE "\\" "/" PGM_FILES $ENV{PROGRAMFILES})

SET (CMAKE_INSTALL_PREFIX ${PGM_FILES}/UPMC/${CMAKE_PROJECT_NAME} CACHE STRING "Default Install Path" FORCE)
ENDIF(WIN32)

SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")

FIND_PACKAGE( Qt4 REQUIRED )
INCLUDE( ${QT_USE_FILE} )

IF(WIN32)
    SET(CMAKE_CXX_FLAGS "/WL /GR /EHsc" ) 
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
	
	IF(MSVC90)
		SET(CMAKE_DEBUG_POSTFIX "_d_2008")
		SET(CMAKE_RELEASE_POSTFIX "_2008")
	ENDIF(MSVC90)
	
	IF(MSVC80)
		SET(CMAKE_DEBUG_POSTFIX "_d_2005")
		SET(CMAKE_RELEASE_POSTFIX "_2005")
	ENDIF(MSVC80)
	
	IF(MSVC71)
		SET(CMAKE_DEBUG_POSTFIX "_d_2003")
		SET(CMAKE_RELEASE_POSTFIX "_2003")
	ENDIF(MSVC71)
	
	IF(MSVC70)
		SET(CMAKE_DEBUG_POSTFIX "_d_2002")
		SET(CMAKE_RELEASE_POSTFIX "_2002")
	ENDIF(MSVC70)
	
	IF(MSVC60)
		SET(CMAKE_DEBUG_POSTFIX "_d")
		SET(CMAKE_RELEASE_POSTFIX "_vc6")
	ENDIF(MSVC60)
	
ELSE(WIN32)
	SET(CMAKE_DEBUG_POSTFIX "_d")
ENDIF(WIN32)

set (QTBASICUTILS_VERSION_MAJOR 1)
set (QTBASICUTILS_VERSION_MINOR 0)

configure_file (
	"${PROJECT_SOURCE_DIR}/QtBasicUtilsConfig.h.in"
	"${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.h"
)

set (QTBASICUTILS_INCLUDE  ${CMAKE_INSTALL_PREFIX}/include )
set (QTBASICUTILS_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (QTBASICUTILS_RELEASE_LIB ${PROJECT_NAME} )
set (QTBASICUTILS_DEBUG_LIB ${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

configure_file (
	"${PROJECT_SOURCE_DIR}/QtBasicUtilsConfig.cmake.in"
	"${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.cmake"
)

export_library_dependencies (
	"${PROJECT_BINARY_DIR}/QtBasicUtilsLibraryDepends.cmake"
)

SET( QtBasicUtils_SRCS
	./src/main.cxx
	./src/QCmd.cxx
	./src/QCmdLine.cxx
	./src/QCmdPart.cxx
	./src/QCmdOpt.cxx
	./src/QCmdHelpException.cxx
	./src/QCmdParseException.cxx
	./src/QCmdParseError.cxx
	./src/QCmdOptBool.cxx
	./src/QCmdOptQChar.cxx
	./src/QCmdOptQString.cxx
	./src/QCmdOptQStringList.cxx
	./src/QCmdArg.cxx
	./src/QCmdArgBool.cxx
	./src/QCmdArgQChar.cxx
	./src/QCmdArgQString.cxx
	./src/QCmdArgQStringList.cxx
	./src/QCmdArgFileList.cxx
	./src/QCmdLineFileList.cxx
	./src/QCmdHelp.cxx
)

SET( QtBasicUtils_EXT_HDRS 
	./include/QtBasicUtils.h
	./include/QLimits.h
	./include/QCmd.h
	./include/QCmdLine.h
	./include/QCmdExtra.h
	./include/QCmdParseError.h
	./include/QCmdHelpException.h
	./include/QCmdParseException.h
	./include/QCmdLineFileList.h
	./include/QCmdPart.h
	./include/QCmdArg.h
	./include/QCmdOpt.h
	./include/QCmdOptBasicBase.h
	./include/QCmdOptBasicBase.txx
	./include/QCmdOptBasicBaseMM.h
	./include/QCmdOptBasicBaseMM.txx
	./include/QCmdOptBasic.h
	./include/QCmdOptBasic.txx
	./include/QCmdOptBool.h
	./include/QCmdOptQChar.h
	./include/QCmdOptQString.h
	./include/QCmdOptQStringList.h
	./include/QCmdArgBool.h
	./include/QCmdArgBasic.h
	./include/QCmdArgBasic.txx
	./include/QCmdArgBasicBase.h
	./include/QCmdArgBasicBase.txx
	./include/QCmdArgBasicBaseMM.h
	./include/QCmdArgBasicBaseMM.txx
	./include/QCmdArgQChar.h
	./include/QCmdArgQString.h
	./include/QCmdArgQStringList.h
	./include/QCmdArgFileList.h
	./include/QCmdHelp.h
)

SET( QtBasicUtils_INT_HDRS
	"${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.h"
)

IF(BUILD_TESTING)
ENABLE_TESTING()
#include(Testing/UnitTests.cmake)
add_subdirectory(Testing)
ENDIF(BUILD_TESTING)

IF(BUILD_EXPERIMENTAL)
add_subdirectory(Experimental)
ENDIF(BUILD_EXPERIMENTAL)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

include_directories( ${PROJECT_BINARY_DIR} ${PROJECT_BINARY_DIR}/.. ${PROJECT_SOURCE_DIR}/include )

add_library(QtBasicUtils ${QtBasicUtils_SRCS} ${QtBasicUtils_EXT_HDRS} ${QtBasicUtils_INT_HDRS} )

install (FILES
	${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.cmake
	${PROJECT_BINARY_DIR}/QtBasicUtilsLibraryDepends.cmake
	${PROJECT_SOURCE_DIR}/QtBasicUtilsUse.cmake
	DESTINATION lib
)

install (TARGETS QtBasicUtils DESTINATION lib)
install (FILES ${QtBasicUtils_EXT_HDRS} DESTINATION include)


