PROJECT(QtBasicUtils)

CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#get_property( PredefinedTargetsFolderName GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER )
#set_target_properties(ALL_BUILD PROPERTIES FOLDER PredefinedTargetsFolderName)

set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 0)
set (${PROJECT_NAME}_VERSION_PATCH 0)
set (${PROJECT_NAME}_VERSION_STRING "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}")

include(${PROJECT_SOURCE_DIR}/CMake/SubversionVersionInfo.cmake)

#########################################################################################

#Do not complain about relative link paths.
cmake_policy(SET CMP0015 NEW)

#########################################################################################

option (BUILD_TESTING 				"Build Tests" ON)
option (BUILD_EXPERIMENTAL 			"Build Experimental Code" ON)
option (BUILD_DOCUMENTATION			"Generate doxygen documentation" OFF)

#########################################################################################

include(${PROJECT_SOURCE_DIR}/CMake/GetRuntime.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/SiteConfig.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/GetCompilerVersion.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/SetupDefaultInstallPath.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/HelperMacros.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/SetCompilerOptions.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/SelectDefaultConfigurations.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/DisableMSVCWarn.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/MSVCPCHSupport.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/MSVC64BitPortability.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/NamingConvention.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/SetupDefaultInstallPath.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/DisableBufferSecurityCheck.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/NamingConvention.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/SupportRunJobs.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/GenerateInstallScript.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/GenerateUpdateScript.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/GenerateConfigureScript.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/doxygen.cmake)

#########################################################################################

SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")

FIND_PACKAGE( Qt4 REQUIRED )
set(QT_USE_QTXML true)
INCLUDE( ${QT_USE_FILE} )

# The following line will add support to copy the Qt dlls to the Debug and Release folders 
# so that you can debug the application without the user having to deal with .dll path 
# settings inside visual studio. 
include(${PROJECT_SOURCE_DIR}/CMake/GetQtRuntime.cmake)

configure_file (
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h"
)

set (${PROJECT_NAME}_INCLUDE  ${CMAKE_INSTALL_PREFIX}/include )
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

add_library(${PROJECT_NAME} 
	${${PROJECT_NAME}_SRCS} 
	${${PROJECT_NAME}_EXT_HDRS} 
	${${PROJECT_NAME}_MOC_HDRS} 
	${${PROJECT_NAME}_MOC_SRCS} 
	${${PROJECT_NAME}_INT_HDRS} 
)

set( ${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include )
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
install (FILES ${${PROJECT_NAME}_EXT_HDRS} ${${PROJECT_NAME}_MOC_HDRS} DESTINATION include)

#########################################################################################


IF(BUILD_DOCUMENTATION)

ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/src)
ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_subdirectory(doxygen)
ENDIF(BUILD_DOCUMENTATION)


