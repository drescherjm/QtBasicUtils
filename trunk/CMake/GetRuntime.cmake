option (GET_RUNTIME			"Create a target that will get the runtime" ON)

IF (GET_RUNTIME) 

    SET (${PROJECT_NAME}_RELEASE_RUNTIME "")
	SET (${PROJECT_NAME}_DEBUG_RUNTIME "")

	SET (RUNTIME_BATCH_FILENAME "${PROJECT_BINARY_DIR}/GetRuntime.bat" CACHE FILEPATH "${PROJECT_BINARY_DIR}/GetRuntime.bat")
	
	add_custom_target(GetRuntime  "${RUNTIME_BATCH_FILENAME}")
	
#########################################################################################

	macro( add_runtime_file BatchFileName RuntimeFile Configuration )

		# Test if this is a valid configuration.
		STRING( REGEX MATCH ${Configuration} __MATCHED__ ${CMAKE_CONFIGURATION_TYPES})
		if ( NOT "${__MATCHED__}" STREQUAL "" )
		
			if (NOT EXISTS "${EXECUTABLE_OUTPUT_PATH}/${Configuration}")
				file( MAKE_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}/${Configuration}" )
			endif (NOT EXISTS "${EXECUTABLE_OUTPUT_PATH}/${Configuration}")
		
			GET_FILENAME_COMPONENT( BatchFile ${BatchFileName} NAME_WE )
			
			#The following will truncate the file on the first call to add_runtime_file.
			if ( NOT DEFINED __add_runtime_file_${BatchFile}__ ) 
				set ( __add_runtime_file_${BatchFile}__ 1)
				file( WRITE ${BatchFileName} "REM This file will copy the runtimes to the Debug and Release binary folders\n" )
			endif ( NOT DEFINED __add_runtime_file_${BatchFile}__)
			
			#The following line will add the entry in the batch file for copying the Runtime file to the folder ${PROJECT_BINARY_DIR}/${Configuration}/
			file( APPEND ${BatchFileName} "\"${CMAKE_COMMAND}\" -E copy_if_different \"${RuntimeFile}\" \"${EXECUTABLE_OUTPUT_PATH}/${Configuration}/\"\n" )
		endif(  NOT "${__MATCHED__}" STREQUAL "" )
	endmacro( add_runtime_file )
	
#########################################################################################

	macro( add_runtime_file_release BatchFileName RuntimeFile Release )
		add_runtime_file( ${BatchFileName} ${RuntimeFile} ${Release} )
	    add_runtime_file( ${RUNTIME_BATCH_FILENAME} ${RuntimeFile} Release )
		add_runtime_file( ${RUNTIME_BATCH_FILENAME} ${RuntimeFile} RelWithDebInfo )
		SET( ${PROJECT_NAME}_RELEASE_RUNTIME  ${${PROJECT_NAME}_RELEASE_RUNTIME} ${RuntimeFile} )
	endmacro( add_runtime_file_release )
	
ENDIF(GET_RUNTIME)