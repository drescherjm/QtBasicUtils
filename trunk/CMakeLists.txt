PROJECT(QtBasicUtils)

CMAKE_MINIMUM_REQUIRED (VERSION 2.6 FATAL_ERROR)

#########################################################################################

option (BUILD_TESTING "Build Tests" ON)
option (BUILD_EXPERIMENTAL "Build Experimental Code" ON)
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

IF(WIN32)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
ENDIF(WIN32)

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
set (CMAKE_INSTALL_PREFIX ${DEFAULT_INSTALL_PATH} CACHE STRING "Install path" FORCE)

ENDIF(WIN32)

#########################################################################################

MACRO(ADD_TO_DOC FOLDER_TO_ADD_TO_DOCS)
     SET( DOXYGEN_SOURCE_DIR ${DOXYGEN_SOURCE_DIR} ${FOLDER_TO_ADD_TO_DOCS} CACHE INTERNAL "List of folders to add to the documentation.")
ENDMACRO(ADD_TO_DOC)

#########################################################################################

MACRO(ADD_TO_DISTCLEAN TARGET_TO_DELETE)
     SET( FILES_TO_DELETE ${FILES_TO_DELETE} ${TARGET_TO_DELETE} )
ENDMACRO(ADD_TO_DISTCLEAN)

#########################################################################################

# Create a "make doc" target using Doxygen
# Prototype:
#     GENERATE_DOCUMENTATION(doxygen_config_file)
# Parameters:

# doxygen_config_file Doxygen configuration file (must in root/doxygen of the source directory) 

MACRO(GENERATE_DOCUMENTATION DOXYGEN_CONFIG_FILE)
FIND_PACKAGE(Doxygen REQUIRED)
SET(DOXYFILE_FOUND false)
IF(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_CONFIG_FILE})
    SET(DOXYFILE_FOUND true)
ENDIF(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_CONFIG_FILE})

IF( DOXYGEN_FOUND )
    IF( DOXYFILE_FOUND )
        # Add target

ADD_CUSTOM_TARGET( documentation ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_CONFIG_FILE}" > "${CMAKE_CURRENT_BINARY_DIR}/doxygen.log" )

# Add .tag file and generated documentation to the list of files we must erase when distcleaning

        # Read doxygen configuration file

FILE( READ ${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_CONFIG_FILE} DOXYFILE_CONTENTS )

        STRING( REGEX REPLACE "\n" ";" DOXYFILE_LINES ${DOXYFILE_CONTENTS} )

        # Parse .tag filename and add to list of files to delete if it exists
        FOREACH( DOXYLINE ${DOXYFILE_CONTENTS} )

STRING( REGEX REPLACE ".*GENERATE_TAGFILE *= *([^ ^\n]+).*" "\\1" DOXYGEN_TAG_FILE ${DOXYLINE} )

        ENDFOREACH( DOXYLINE )
        ADD_TO_DISTCLEAN( ${PROJECT_BINARY_DIR}/${DOXYGEN_TAG_FILE} )


# Parse doxygen output doc dir and add to list of files to delete if it exists

        FOREACH( DOXYLINE ${DOXYFILE_CONTENTS} )

STRING( REGEX REPLACE ".*OUTPUT_DIRECTORY *= *([^ ^\n]+).*" "\\1" DOXYGEN_DOC_DIR ${DOXYLINE} )

        ENDFOREACH( DOXYLINE )
        ADD_TO_DISTCLEAN( ${PROJECT_BINARY_DIR}/${DOXYGEN_DOC_DIR} )
        ADD_TO_DISTCLEAN( ${PROJECT_BINARY_DIR}/${DOXYGEN_DOC_DIR}.dir )

    ELSE( DOXYFILE_FOUND )

MESSAGE( STATUS "Doxygen configuration file not found - Documentation will not be generated" )

    ENDIF( DOXYFILE_FOUND )
ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found - Documentation will not be generated")
ENDIF(DOXYGEN_FOUND)
ENDMACRO(GENERATE_DOCUMENTATION)

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
    SET(CMAKE_CXX_FLAGS "/MP /WL /GR /EHa" ) 
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

#########################################################################################


IF(BUILD_DOCUMENTATION)

ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/src)
ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_subdirectory(doxygen)
ENDIF(BUILD_DOCUMENTATION)


