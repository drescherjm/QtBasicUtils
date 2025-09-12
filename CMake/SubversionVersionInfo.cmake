#-----------------------------------------------------------------------------
# If subversion is found append the svn rev to the patch version.
#
FIND_PACKAGE(Subversion)
IF(Subversion_FOUND)
	OPTION(SVN_APPEND_REV "Append subversion rev to application version" ON)
	IF(SVN_APPEND_REV)
		Subversion_WC_INFO(${PROJECT_SOURCE_DIR} Project)
		MESSAGE("Current revision is ${Project_WC_REVISION}")
		
		OPTION(SVN_GET_LOG "Get the SVN LOG" OFF)
		if(SVN_GET_LOG)
			Subversion_WC_LOG(${PROJECT_SOURCE_DIR} Project)
			MESSAGE("Last changed log is ${Project_LAST_CHANGED_LOG}")
		endif(SVN_GET_LOG)
	
		set (${PROJECT_NAME}_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH}.${Project_WC_REVISION})
	ENDIF(SVN_APPEND_REV)
	
ENDIF(Subversion_FOUND)