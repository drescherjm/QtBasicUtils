# --------------------------------------------------------------------
# Copy the needed Qt libraries into the Build directory. Also add installation
# and CPack code to support installer generation.
# --------------------------------------------------------------------

if (GET_RUNTIME)

#########################################################################################

	macro( add_qt_sqldriver_file BatchFileName RuntimeFile Release )

		GET_FILENAME_COMPONENT( BatchFile ${BatchFileName} NAME_WE )
		
		#The following will truncate the file on the first call to add_qt_sqldriver_file.
		if ( NOT DEFINED __add_runtime_file_${BatchFile}__ ) 
			set ( __add_runtime_file_${BatchFile}__ 1)
			file( WRITE ${BatchFileName} "REM This file will copy the runtimes to the Debug and Release binary folders\n" )
		endif ( NOT DEFINED __add_runtime_file_${BatchFile}__)
		
		message( STATUS "CREATING ${EXECUTABLE_OUTPUT_PATH}/${Release}/sqldrivers")
		file( MAKE_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}/${Release}/sqldrivers" )
		#The following line will add the entry in the batch file for copying the Runtime file to the folder ${PROJECT_BINARY_DIR}/${Release}/
		file( APPEND ${BatchFileName} "@\"${CMAKE_COMMAND}\" -E copy_if_different \"${RuntimeFile}\" \"${EXECUTABLE_OUTPUT_PATH}/${Release}/sqldrivers/\"\n" )
		
	endmacro( add_qt_sqldriver_file )
	
#########################################################################################

	macro( add_sqldriver_file_release BatchFileName RuntimeFile Release )
		add_qt_sqldriver_file( ${BatchFileName} ${RuntimeFile} ${Release} )
		#SET( ${PROJECT_NAME}_RELEASE_RUNTIME  ${${PROJECT_NAME}_RELEASE_RUNTIME} ${RuntimeFile} )
		
		INSTALL(FILES ${RuntimeFile}
			DESTINATION bin/sqldrivers
			COMPONENT Applications
		)
		
	endmacro( add_sqldriver_file_release )
	
#########################################################################################	

	IF (WIN32)
		FOREACH(LIB QtCore QtXml QtGui QtNetwork QtSql)
				add_runtime_file( ${RUNTIME_BATCH_FILENAME} "${QT_BINARY_DIR}/${LIB}d${QT_VERSION_MAJOR}.dll" Debug )
				add_runtime_file_release( ${RUNTIME_BATCH_FILENAME} "${QT_BINARY_DIR}/${LIB}${QT_VERSION_MAJOR}.dll" RelWithDebInfo )
		ENDFOREACH(LIB)
		
		add_qt_sqldriver_file( ${RUNTIME_BATCH_FILENAME} "${QT_PLUGINS_DIR}/sqldrivers/qsqlited${QT_VERSION_MAJOR}.dll" Debug )
		add_sqldriver_file_release( ${RUNTIME_BATCH_FILENAME} "${QT_PLUGINS_DIR}/sqldrivers/qsqlite${QT_VERSION_MAJOR}.dll" RelWithDebInfo )
		
	ENDIF(WIN32)
endif(GET_RUNTIME)