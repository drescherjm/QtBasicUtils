PROJECT(QtBasicUtils)

CMAKE_MINIMUM_REQUIRED (VERSION 2.6 FATAL_ERROR)

#########################################################################################

option (BUILD_TESTING "Build Tests" ON)
option (BUILD_EXPERIMENTAL "Build Experimental Code" ON)
option (MAKE_DEBUGRELEASE 			"Add support for building a Release Target with debug info" ON)

IF(WIN32)

#The following command changes \ to / in the Program Files Path so CMake will not complain
#about bad escape sequences.
IF(CMAKE_SIZEOF_VOID_P MATCHES 4)
string (REPLACE "\\" "/" PGM_FILES $ENV{PROGRAMFILES})
ELSE(CMAKE_SIZEOF_VOID_P MATCHES 4)
# On WIN64 use the 64 bit program files..
string (REPLACE "\\" "/" PGM_FILES $ENV{ProgramW6432})
ENDIF(CMAKE_SIZEOF_VOID_P MATCHES 4)

SET (DEFAULT_INSTALL_PATH ${PGM_FILES}/UPMC/${CMAKE_PROJECT_NAME} CACHE STRING "Default Install Path")

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
   set (CMAKE_INSTALL_PREFIX ${DEFAULT_INSTALL_PATH} CACHE FORCE)
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

ENDIF(WIN32)

#########################################################################################

IF (MAKE_DEBUGRELEASE)
SET (CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo" CACHE STRING "Debug;RelWithDebInfo" FORCE)
SET (RELEASE_BUILD_NAME "RelWithDebInfo")
ELSE(MAKE_DEBUGRELEASE)
SET (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug;Release" FORCE)
SET (RELEASE_BUILD_NAME "Release")
ENDIF (MAKE_DEBUGRELEASE)

IF(WIN32)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
ENDIF(WIN32)

SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")

FIND_PACKAGE( Qt4 REQUIRED )
set(QT_USE_QTXML true)
INCLUDE( ${QT_USE_FILE} )

IF(MSVC)
    SET(CMAKE_CXX_FLAGS "/MP /WL /GR /EHsc" ) 
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
	
	IF(MSVC90)
		SET(CMAKE_DEBUG_POSTFIX "_d_2008")
		SET(CMAKE_RELEASE_POSTFIX "_2008")
		SET(CMAKE_RELWITHDEBINFO_POSTFIX "_2008")
	ENDIF(MSVC90)
	
	IF(MSVC80)
		SET(CMAKE_DEBUG_POSTFIX "_d_2005")
		SET(CMAKE_RELEASE_POSTFIX "_2005")
		SET(CMAKE_RELWITHDEBINFO_POSTFIX "_2005")
	ENDIF(MSVC80)
	
	IF(MSVC71)
		SET(CMAKE_DEBUG_POSTFIX "_d_2003")
		SET(CMAKE_RELEASE_POSTFIX "_2003")
		SET(CMAKE_RELWITHDEBINFO_POSTFIX "_2003")
	ENDIF(MSVC71)
	
	IF(MSVC70)
		SET(CMAKE_DEBUG_POSTFIX "_d_2002")
		SET(CMAKE_RELEASE_POSTFIX "_2002")
		SET(CMAKE_RELWITHDEBINFO_POSTFIX "_2002")
	ENDIF(MSVC70)
	
	IF(MSVC60)
		SET(CMAKE_DEBUG_POSTFIX "_d_vc6")
		SET(CMAKE_RELEASE_POSTFIX "_vc6")
		SET(CMAKE_RELWITHDEBINFO_POSTFIX "_vc6")
	ENDIF(MSVC60)
		
configure_file (
	"${PROJECT_SOURCE_DIR}/install.bat.in"
	"${PROJECT_BINARY_DIR}/Batch/install.bat"
)
ELSE(MSVC)
	SET(CMAKE_DEBUG_POSTFIX "_d")
ENDIF(MSVC)

set (QTBASICUTILS_VERSION_MAJOR 1)
set (QTBASICUTILS_VERSION_MINOR 0)

configure_file (
	"${PROJECT_SOURCE_DIR}/QtBasicUtilsConfig.h.in"
	"${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.h"
)

configure_file (
	"${PROJECT_SOURCE_DIR}/install.bat.in"
	"${PROJECT_BINARY_DIR}/Batch/install.bat"
)

set (QTBASICUTILS_INCLUDE  ${CMAKE_INSTALL_PREFIX}/include )
set (QTBASICUTILS_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (QTBASICUTILS_RELEASE_LIB ${PROJECT_NAME}${CMAKE_RELEASE_POSTFIX} )
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
	./src/Property.cxx
	./src/PropertyMap.cxx
	./src/UserProperty.cxx
	./src/UserPropPtr.cxx
	./src/PropertyList.cxx
	./src/PropXMLHelper.cxx
	./src/QNamedCmdPart.cxx
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
	./include/QNamedCmdPart.h
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
	./include/QUpdateTracker.h
	./include/PropXMLHelper.h
	./include/NonThreadSafeSingleton.h
)

SET( QtBasicUtils_MOC_HDRS 
	./include/Property.h
	./include/PropertyMap.h
	./include/UserPropery.h
	./include/UserPropPtr.h
	./include/PropertyList.h
)

SET( QtBasicUtils_INT_HDRS
	"${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.h"
)

# and finally this will run moc:
QT4_WRAP_CPP( QtBasicUtils_MOC_SRCS ${QtBasicUtils_MOC_HDRS} )

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

add_library(QtBasicUtils 
	${QtBasicUtils_SRCS} 
	${QtBasicUtils_EXT_HDRS} 
	${QtBasicUtils_MOC_HDRS} 
	${QtBasicUtils_MOC_SRCS} 
	${QtBasicUtils_INT_HDRS} 
)

install (FILES
	${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.cmake
	${PROJECT_BINARY_DIR}/QtBasicUtilsLibraryDepends.cmake
	${PROJECT_SOURCE_DIR}/QtBasicUtilsUse.cmake
	DESTINATION lib
)

install (TARGETS QtBasicUtils DESTINATION lib)
install (FILES ${QtBasicUtils_EXT_HDRS} ${QtBasicUtils_MOC_HDRS} DESTINATION include)


