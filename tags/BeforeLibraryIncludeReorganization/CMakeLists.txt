PROJECT(QtBasicUtils)

CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#get_property( PredefinedTargetsFolderName GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER )
#set_target_properties(ALL_BUILD PROPERTIES FOLDER PredefinedTargetsFolderName)

set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 3)
set (${PROJECT_NAME}_VERSION_PATCH 0)
set (${PROJECT_NAME}_VERSION_STRING "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}")

Include(${PROJECT_SOURCE_DIR}/CMake/SubversionVersionInfo.cmake)

#########################################################################################

#Do not complain about relative link paths.
cmake_policy(SET CMP0015 NEW)

#########################################################################################

option (BUILD_TESTING 				"Build Tests" ON)
option (BUILD_EXPERIMENTAL 			"Build Experimental Code" ON)
option (BUILD_DOCUMENTATION			"Generate doxygen documentation" OFF)
option (DEBUG_ASSERT_CMDLINE		"Assert on command line exceptions in debug mode" ON)

#########################################################################################

Include(${PROJECT_SOURCE_DIR}/CMake/GetRuntime.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/SiteConfig.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/GetCompilerVersion.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/SetupDefaultInstallPath.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/HelperMacros.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/SetCompilerOptions.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/SelectDefaultConfigurations.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/DisableMSVCWarn.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/MSVCPCHSupport.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/MSVC64BitPortability.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/NamingConvention.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/SetupDefaultInstallPath.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/DisableBufferSecurityCheck.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/NamingConvention.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/SupportRunJobs.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/GenerateInstallScript.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/GenerateUpdateScript.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/GenerateConfigureScript.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/doxygen.cmake)

#########################################################################################

SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")

FIND_PACKAGE( Qt4 REQUIRED )
set(QT_USE_QTXML true)
INCLUDE( ${QT_USE_FILE} )

# The following line will add support to copy the Qt dlls to the Debug and Release folders 
# so that you can debug the application without the user having to deal with .dll path 
# settings inside visual studio. 
Include(${PROJECT_SOURCE_DIR}/CMake/GetQtRuntime.cmake)

configure_file (
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h"
)

conditional_define(DEBUG_ASSERT_CMDLINE DEBUG_ASSERT_CMDLINE)

set (${PROJECT_NAME}_INCLUDE  ${CMAKE_INSTALL_PREFIX}/Include )
set (${PROJECT_NAME}_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (${PROJECT_NAME}_RELEASE_LIB ${PROJECT_NAME}${CMAKE_RELEASE_POSTFIX} )
set (${PROJECT_NAME}_DEBUG_LIB ${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

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
	./src/ProperyMapXMLHelper.cxx
	./src/QNamedCmdPart.cxx
	./src/qbuITKIndent.cxx
)

SET( ${PROJECT_NAME}_EXT_HDRS 
	./Include/${PROJECT_NAME}.h
	./Include/QCmdLine.h
	./Include/QCmdExtra.h
	./Include/QCmdParseError.h
	./Include/QCmdHelpException.h
	./Include/QCmdParseException.h
	./Include/QCmdLineFileList.h
	./Include/QCmdPart.h
	./Include/QNamedCmdPart.h
	./Include/QCmdArg.h
	./Include/QCmdOpt.h
	./Include/QCmdOptBasicBase.h
	./Include/QCmdOptBasicBase.txx
	./Include/QCmdOptBasicBaseMM.h
	./Include/QCmdOptBasicBaseMM.txx
	./Include/QCmdOptBasic.h
	./Include/QCmdOptBasic.txx
	./Include/QCmdOptBool.h
	./Include/QCmdOptQChar.h
	./Include/QCmdOptQString.h
	./Include/QCmdOptQStringList.h
	./Include/QCmdArgBool.h
	./Include/QCmdArgBasic.h
	./Include/QCmdArgBasic.txx
	./Include/QCmdArgBasicBase.h
	./Include/QCmdArgBasicBase.txx
	./Include/QCmdArgBasicBaseMM.h
	./Include/QCmdArgBasicBaseMM.txx
	./Include/QCmdArgQChar.h
	./Include/QCmdArgQString.h
	./Include/QCmdArgQStringList.h
	./Include/QCmdArgFileList.h
	./Include/QCmdHelp.h
	./Include/QUpdateTracker.h
	./Include/PropXMLHelper.h
	./Include/ProperyMapXMLHelper.h
	./Include/NonThreadSafeSingleton.h
	./Include/qbuITKIndent.h
)

SET( ${PROJECT_NAME}_MOC_HDRS 
	./Include/QCmd.h
	./Include/Property.h
	./Include/PropertyMap.h
	./Include/UserPropery.h
	./Include/UserPropPtr.h
	./Include/PropertyList.h
)

SET( ${PROJECT_NAME}_INT_HDRS
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h"
)

# and finally this will run moc:
QT4_WRAP_CPP( ${PROJECT_NAME}_MOC_SRCS ${${PROJECT_NAME}_MOC_HDRS} )

IF(BUILD_TESTING)
ENABLE_TESTING()
#Include(Testing/UnitTests.cmake)
add_subdirectory(Testing)
ENDIF(BUILD_TESTING)

IF(BUILD_EXPERIMENTAL)
add_subdirectory(Experimental)
ENDIF(BUILD_EXPERIMENTAL)

add_subdirectory(Libraries)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

include_directories( ${PROJECT_BINARY_DIR} ${PROJECT_BINARY_DIR}/.. ${PROJECT_SOURCE_DIR}/Include )

#########################################################################################

add_library(${PROJECT_NAME} 
	${${PROJECT_NAME}_SRCS} 
	${${PROJECT_NAME}_EXT_HDRS} 
	${${PROJECT_NAME}_MOC_HDRS} 
	${${PROJECT_NAME}_MOC_SRCS} 
	${${PROJECT_NAME}_INT_HDRS} 
)

set( ${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Include )
export( TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Exported.cmake)

configure_file (
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
)

configure_file (
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}USE.cmake.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}USE.cmake"
	@ONLY
)

install (FILES
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}LibraryDepends.cmake
	${PROJECT_SOURCE_DIR}/${PROJECT_NAME}USE.cmake
	DESTINATION lib
)

install (TARGETS ${PROJECT_NAME} DESTINATION lib)
install (FILES ${${PROJECT_NAME}_EXT_HDRS} ${${PROJECT_NAME}_MOC_HDRS} DESTINATION Include)

#########################################################################################


IF(BUILD_DOCUMENTATION)

ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/src)
ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_subdirectory(doxygen)
ENDIF(BUILD_DOCUMENTATION)


