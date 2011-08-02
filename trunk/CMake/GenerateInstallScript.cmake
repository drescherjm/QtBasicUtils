# This script will generate a script to build the project in all of its configurations

macro( setup_build_command_for_script ReleaseType Variable)
	LIST_CONTAINS_IGNORE_CASE(contains ${ReleaseType} ${PROJECT_CONFIGURATION_TYPES})
	if (contains)
		if (NOT "${ARGN}" STREQUAL "") 
			set( ${Variable} "cmake --build ${PROJECT_BINARY_DIR} --config ${ReleaseType} --target ${ARGN}" )
		else(NOT "${ARGN}" STREQUAL "") 
			set( ${Variable} "cmake --build ${PROJECT_BINARY_DIR} --config ${ReleaseType}" )
		endif(NOT "${ARGN}" STREQUAL "") 
	else(contains)
		set( ${Variable} )
	endif(contains)
endmacro( setup_build_command_for_script )

setup_build_command_for_script( RelWithDebInfo BUILD_CMD1 clean)
setup_build_command_for_script( Release BUILD_CMD2 clean)
setup_build_command_for_script( Debug BUILD_CMD3 clean)
setup_build_command_for_script( MinSizeRel BUILD_CMD4 clean)
set ( BUILD_CMD5 )
set ( BUILD_CMD6 )
set ( BUILD_CMD7 )
set ( BUILD_CMD8 )

configure_file( 	
	"${PROJECT_SOURCE_DIR}/install.bat.in"
	"${PROJECT_BINARY_DIR}/Batch/clean.bat"
)

#########################################################################################

set ( BUILD_CMD0 )
set ( BUILD_CMD1 )
set ( BUILD_CMD2 )
set ( BUILD_CMD3 )
set ( BUILD_CMD4 )
set ( BUILD_CMD5 )
set ( BUILD_CMD6 )
set ( BUILD_CMD7 )
set ( BUILD_CMD8 )
set ( BUILD_CMD9 )
set ( BUILD_CMD10 )

FILE( TO_NATIVE_PATH "${PROJECT_BINARY_DIR}" PROJECT_BUILD_FOLDER_NATIVE )

set ( BUILD_CMD0 "pushd ." )
set ( BUILD_CMD1 "cd ${PROJECT_BUILD_FOLDER_NATIVE}" )
set ( BUILD_CMD2 "cmake ${PROJECT_SOURCE_DIR}" )
set ( BUILD_CMD3 "popd" )

configure_file( 	
	"${PROJECT_SOURCE_DIR}/install.bat.in"
	"${PROJECT_BINARY_DIR}/Batch/configure.bat"
)

#########################################################################################

set ( BUILD_CMD5 )
set ( BUILD_CMD6 )
set ( BUILD_CMD7 )
set ( BUILD_CMD8 )

set ( BUILD_CMD0 "call ${PROJECT_BINARY_DIR}/GetRuntime.bat" )

setup_build_command_for_script( RelWithDebInfo BUILD_CMD1)
setup_build_command_for_script( Release BUILD_CMD2)
setup_build_command_for_script( Debug BUILD_CMD3)
setup_build_command_for_script( MinSizeRel BUILD_CMD4)
#setup_build_command_for_script( RelWithDebInfo BUILD_CMD5 INSTALL)
#setup_build_command_for_script( Release BUILD_CMD6 INSTALL)
#setup_build_command_for_script( Debug BUILD_CMD7 INSTALL)
#setup_build_command_for_script( MinSizeRel BUILD_CMD8 INSTALL)

if (USE_RUNJOBS_PARALLEL_BUILDING)
	configure_file( 	
		"${PROJECT_SOURCE_DIR}/install.bat.in"
		"${PROJECT_BINARY_DIR}/Batch/build.job"
	)
	
	set ( BUILD_CMD1 "${RUNJOBS_EXECUTABLE} ${PROJECT_BINARY_DIR}/Batch/build.job" )
	set ( BUILD_CMD2 )
	set ( BUILD_CMD3 )
	set ( BUILD_CMD4 )
	set ( BUILD_CMD5 )
	set ( BUILD_CMD6 )
	set ( BUILD_CMD7 )
	set ( BUILD_CMD8 )
	
endif(USE_RUNJOBS_PARALLEL_BUILDING)

configure_file( 	
	"${PROJECT_SOURCE_DIR}/install.bat.in"
	"${PROJECT_BINARY_DIR}/Batch/install.bat"
)
