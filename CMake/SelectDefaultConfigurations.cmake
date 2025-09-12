#########################################################################################
#
#	Note: This file sets the default configurations to be CMAKE_DEFAULT_CONFIGURATIONS or
#	the environment variable CMAKE_DEFAULT_CONFIGURATIONS if defined. Otherwise it 
# 	will use the default CMAKE_CONFIGURATION_TYPES.
#
#########################################################################################

macro( RESET_CONFIGURATION_TYPES )
	SET (CMAKE_CONFIGURATION_TYPES ${PROJECT_CONFIGURATION_TYPES} CACHE STRING 
	"Please select the configurations to use with this project or set the CMAKE_DEFAULT_CONFIGURATIONS envronment variable to your selection." FORCE)
endmacro( RESET_CONFIGURATION_TYPES )

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    #Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if (NOT CMAKE_BUILD_TYPE) 

	MESSAGE( STATUS "Processing a multiconfig generator" )

	if( NOT CMAKE_DEFAULT_CONFIGURATIONS AND NOT "$ENV{CMAKE_DEFAULT_CONFIGURATIONS}" STREQUAL "" )
		SET (PROJECT_CONFIGURATION_TYPES "$ENV{CMAKE_DEFAULT_CONFIGURATIONS}" )
	else( NOT CMAKE_DEFAULT_CONFIGURATIONS AND NOT "$ENV{CMAKE_DEFAULT_CONFIGURATIONS}" STREQUAL "" )
		SET (PROJECT_CONFIGURATION_TYPES ${CMAKE_CONFIGURATION_TYPES})
	endif( NOT CMAKE_DEFAULT_CONFIGURATIONS AND NOT "$ENV{CMAKE_DEFAULT_CONFIGURATIONS}" STREQUAL "" )

	#MESSAGE( STATUS "PROJECT_CONFIGURATION_TYPES: " ${PROJECT_CONFIGURATION_TYPES} )
	print_list( "PROJECT_CONFIGURATION_TYPES:" ${PROJECT_CONFIGURATION_TYPES} )

	RESET_CONFIGURATION_TYPES()

	# Determine the release version to package.
	STRING( REGEX MATCH "Release" __MATCHED__ ${CMAKE_CONFIGURATION_TYPES})
	if ("${__MATCHED__}" STREQUAL "")
		STRING( REGEX MATCH "MinSizeRel" __MATCHED__ ${CMAKE_CONFIGURATION_TYPES})
		if ("${__MATCHED__}" STREQUAL "")
			STRING( REGEX MATCH "RelWithDebInfo" __MATCHED__ ${CMAKE_CONFIGURATION_TYPES})
		endif ("${__MATCHED__}" STREQUAL "")
	endif ("${__MATCHED__}" STREQUAL "")

	SET(PROJECT_PACKAGE_TYPE ${__MATCHED__})
	MESSAGE( STATUS "Release Package Type: " ${PROJECT_PACKAGE_TYPE})
	SET(PROJECT_DEBUG_TYPE Debug)
else(NOT CMAKE_BUILD_TYPE)
	SET(PROJECT_DEBUG_TYPE ${CMAKE_BUILD_TYPE})
endif(NOT CMAKE_BUILD_TYPE)

#########################################################################################
