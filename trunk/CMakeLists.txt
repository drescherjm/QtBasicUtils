project(QtBasicUtils)

cmake_minimum_required (VERSION 3.0 FATAL_ERROR)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (${PROJECT_NAME}_VERSION_MAJOR 2)
set (${PROJECT_NAME}_VERSION_MINOR 0)
set (${PROJECT_NAME}_VERSION_PATCH 0)
set (${PROJECT_NAME}_VERSION_PATCH_CLEAN ${${PROJECT_NAME}_VERSION_PATCH})
set (${PROJECT_NAME}_VERSION_STRING "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}")

include(${PROJECT_SOURCE_DIR}/CMake/SubversionVersionInfo.cmake)

# The following line will add additional finders to CMake without the need to be placed in the CMake install path
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/External/Modules)

#########################################################################################

option (BUILD_TESTING 				"Build Tests" ON)
option (BUILD_DEVELOPMENT 			"Build Development Code" ON)
option (BUILD_DOCUMENTATION			"Generate doxygen documentation" OFF)
option (DEBUG_ASSERT_CMDLINE		"Assert on command line exceptions in debug mode" ON)

#########################################################################################

Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/GetRuntime.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/SiteConfig.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/GetCompilerVersion.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/SetupDefaultInstallPath.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/SetupProject.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/HelperMacros.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/SetCompilerOptions.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/SelectDefaultConfigurations.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/DisableMSVCWarn.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/MSVCPCHSupport.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/NamingConvention.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/SetupDefaultInstallPath.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/DisableBufferSecurityCheck.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/NamingConvention.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/SupportRunJobs.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/GenerateInstallScript.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/GenerateUpdateScript.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/GenerateConfigureScript.cmake)
Include(${PROJECT_SOURCE_DIR}/CMake/doxygen.cmake)
include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/SupportQt.cmake)
include(GenerateExportHeader)

#########################################################################################

set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Libraries/Include)

if(${PROJECT_NAME}_QT_VERSION VERSION_GREATER "4")

	set (QT_LIBRARIES Qt5::Widgets Qt5::WinMain Qt5::Xml)
	set (QT_MODULES Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WinMain Qt5::Xml)
	
	find_qt5_packages()
		
else(${PROJECT_NAME}_QT_VERSION VERSION_GREATER "4")
	set(QT_USE_QTXML true)
	set(QT_USE_QTDESIGNER true)
	find_package(Qt4 REQUIRED)
	include(${QT_USE_FILE})
endif(${PROJECT_NAME}_QT_VERSION VERSION_GREATER "4")

message( STATUS "LOCAL_PROJECT_NAME: ${LOCAL_PROJECT_NAME} - Qt5Core_MOC_EXECUTABLE=${Qt5Core_MOC_EXECUTABLE}" )

# The following line will add support to copy the Qt dlls to the Debug and Release folders 
# so that you can debug the application without the user having to deal with .dll path 
# settings inside visual studio. 
Include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/GetQtRuntime.cmake)

configure_file (
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h"
)

conditional_define(DEBUG_ASSERT_CMDLINE DEBUG_ASSERT_CMDLINE)

#########################################################################################

set( ${PROJECT_NAME}_SRCS

)

set( ${PROJECT_NAME}_EXT_HDRS 
	./Include/${PROJECT_NAME}.h

)

set( ${PROJECT_NAME}_MOC_HDRS 
	

)

set( ${PROJECT_NAME}_INT_HDRS
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h"
)

# and finally this will run moc:
QT45_WRAP_CPP( ${PROJECT_NAME}_MOC_SRCS ${${PROJECT_NAME}_MOC_HDRS} )

#########################################################################################

add_subdirectory(Libraries)

if(BUILD_TESTING)
	ENABLE_TESTING()
	add_subdirectory(Testing)
endif(BUILD_TESTING)

if(BUILD_DEVELOPMENT)
	add_subdirectory(Development)
endif(BUILD_DEVELOPMENT)

#########################################################################################

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

#set( ${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Include )
export( TARGETS ${${PROJECT_NAME}_LIBRARIES} FILE ${PROJECT_NAME}Exported.cmake)

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

#########################################################################################

if(BUILD_DOCUMENTATION)

	ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/src)
	ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/Include)

add_subdirectory(doxygen)
endif(BUILD_DOCUMENTATION)

#dump_all_variables_starting_with( ${PROJECT_NAME} )
#dump_all_variables()