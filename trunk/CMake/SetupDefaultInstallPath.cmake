#########################################################################################

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
	
	configure_file (
		"${PROJECT_SOURCE_DIR}/install.bat.in"
		"${PROJECT_BINARY_DIR}/Batch/install.bat"
	)

ENDIF(WIN32)