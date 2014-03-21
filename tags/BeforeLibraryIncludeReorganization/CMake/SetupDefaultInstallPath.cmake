#########################################################################################

#IF(WIN32)
	
	# We intentionally do not install to Program Files since on Vista or above this 
	# may not work depending on the user settings.
		
	set (DEFAULT_INSTALL_PATH /${SITE_ORGANIZATION}/${CMAKE_PROJECT_NAME} CACHE STRING "Default Install Path")
	set (CMAKE_INSTALL_PREFIX ${DEFAULT_INSTALL_PATH} CACHE STRING "Install path" FORCE)
	
#ENDIF(WIN32)