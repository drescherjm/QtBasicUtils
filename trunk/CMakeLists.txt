PROJECT(QtBasicUtils)

CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)

set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 0)
set (${PROJECT_NAME}_VERSION_PATCH 0)

include(${PROJECT_SOURCE_DIR}/CMake/SubversionVersionInfo.cmake)

IF(WIN32)
	IF (CMAKE_SIZEOF_VOID_P MATCHES 8)
		set (${PROJECT_NAME}_VERSION_PATCH "${${PROJECT_NAME}_VERSION_PATCH}.win64")
	ENDIF(CMAKE_SIZEOF_VOID_P MATCHES 8)
ENDIF(WIN32)

#########################################################################################

#Do not complain about relative link paths.
cmake_policy(SET CMP0015 NEW)

#########################################################################################

option (BUILD_TESTING 				"Build Tests" ON)
option (BUILD_EXPERIMENTAL 			"Build Experimental Code" ON)
option (MAKE_DEBUGRELEASE 			"Add support for building a Release Target with debug info" ON)
option (BUILD_DOCUMENTATION			"Generate doxygen documentation" OFF)

#########################################################################################

IF (MAKE_DEBUGRELEASE)
SET (CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo" CACHE STRING "Debug;RelWithDebInfo" FORCE)
SET (RELEASE_BUILD_NAME "RelWithDebInfo")
ELSE(MAKE_DEBUGRELEASE)
SET (CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug;Release" FORCE)
SET (RELEASE_BUILD_NAME "Release")
ENDIF (MAKE_DEBUGRELEASE)

#########################################################################################

include(${PROJECT_SOURCE_DIR}/CMake/DisableMSVCWarn.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/MSVCPCHSupport.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/NamingConvention.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/doxygen.cmake)

#########################################################################################

SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")

FIND_PACKAGE( Qt4 REQUIRED )
set(QT_USE_QTXML true)
INCLUDE( ${QT_USE_FILE} )

IF(MSVC)

configure_file (
	"${PROJECT_SOURCE_DIR}/install.bat.in"
	"${PROJECT_BINARY_DIR}/Batch/install.bat"
)

ENDIF(MSVC)


configure_file (
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h"
)

configure_file (
	"${PROJECT_SOURCE_DIR}/install.bat.in"
	"${PROJECT_BINARY_DIR}/Batch/install.bat"
)

set (${PROJECT_NAME}_INCLUDE  ${CMAKE_INSTALL_PREFIX}/include )
set (${PROJECT_NAME}_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (${PROJECT_NAME}_RELEASE_LIB ${PROJECT_NAME}${CMAKE_RELEASE_POSTFIX} )
set (${PROJECT_NAME}_DEBUG_LIB ${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

configure_file (
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
)

export_library_dependencies (
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}LibraryDepends.cmake"
)

SET( ${PROJECT_NAME}_SRCS
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

SET( ${PROJECT_NAME}_EXT_HDRS 
	./include/${PROJECT_NAME}.h
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

SET( ${PROJECT_NAME}_MOC_HDRS 
	./include/Property.h
	./include/PropertyMap.h
	./include/UserPropery.h
	./include/UserPropPtr.h
	./include/PropertyList.h
)

SET( ${PROJECT_NAME}_INT_HDRS
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h"
)

# and finally this will run moc:
QT4_WRAP_CPP( ${PROJECT_NAME}_MOC_SRCS ${${PROJECT_NAME}_MOC_HDRS} )

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

#########################################################################################

IF(MSVC)
FOREACH(DLL QtCore QtXml QtTest QtGui QtNetwork QtScript QtSQL)
        INSTALL(FILES
            "${QT_BINARY_DIR}/${DLL}d${QT_VERSION_MAJOR}.dll"
            DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Debug
        )
		INSTALL(FILES
            "${QT_BINARY_DIR}/${DLL}${QT_VERSION_MAJOR}.dll"
            DESTINATION ${EXECUTABLE_OUTPUT_PATH}/RelWithDebInfo
        )
ENDFOREACH(DLL)
ENDIF(MSVC)

#########################################################################################

add_library(${PROJECT_NAME} 
	${${PROJECT_NAME}_SRCS} 
	${${PROJECT_NAME}_EXT_HDRS} 
	${${PROJECT_NAME}_MOC_HDRS} 
	${${PROJECT_NAME}_MOC_SRCS} 
	${${PROJECT_NAME}_INT_HDRS} 
)

install (FILES
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}LibraryDepends.cmake
	${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Use.cmake
	DESTINATION lib
)

install (TARGETS ${PROJECT_NAME} DESTINATION lib)
install (FILES ${${PROJECT_NAME}_EXT_HDRS} ${${PROJECT_NAME}_MOC_HDRS} DESTINATION include)

#########################################################################################


IF(BUILD_DOCUMENTATION)

ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/src)
ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_subdirectory(doxygen)
ENDIF(BUILD_DOCUMENTATION)


