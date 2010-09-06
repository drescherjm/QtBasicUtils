option (GET_RUNTIME			"Create a target that will get the runtime" ON)

IF (GET_RUNTIME) 

	SET (RUNTIME_BATCH_FILENAME "${PROJECT_BINARY_DIR}/GetRuntime.bat" CACHE FILEPATH "${PROJECT_BINARY_DIR}/GetRuntime.bat")
	
	add_custom_target(GetRuntime  "${RUNTIME_BATCH_FILENAME}")

	macro( add_runtime_file BatchFileName RuntimeFile Release )

		GET_FILENAME_COMPONENT( BatchFile ${BatchFileName} NAME_WE )
		
		#The following will truncate the file on the first call to add_runtime_file.
		if ( NOT DEFINED __add_runtime_file_${BatchFile}__ ) 
			set ( __add_runtime_file_${BatchFile}__ 1)
			file( WRITE ${BatchFileName} "REM This file will copy the runtimes to the Debug and Release binary folders\n" )
		endif ( NOT DEFINED __add_runtime_file_${BatchFile}__)
		
		#The following line will add the entry in the batch file for copying the Runtime file to the folder ${PROJECT_BINARY_DIR}/${Release}/
		file( APPEND ${BatchFileName} "\"${CMAKE_COMMAND}\" -E copy_if_different \"${RuntimeFile}\" \"${EXECUTABLE_OUTPUT_PATH}/${Release}/\"\n" )
		
	endmacro( add_runtime_file )
ENDIF(GET_RUNTIME)