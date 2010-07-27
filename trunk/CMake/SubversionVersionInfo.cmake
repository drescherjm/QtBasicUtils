#-----------------------------------------------------------------------------
# If subversion is found append the svn rev to the patch version.
#
FIND_PACKAGE(Subversion)
IF(Subversion_FOUND)
    Subversion_WC_INFO(${PROJECT_SOURCE_DIR} Project)
    MESSAGE("Current revision is ${Project_WC_REVISION}")
    Subversion_WC_LOG(${PROJECT_SOURCE_DIR} Project)
    MESSAGE("Last changed log is ${Project_LAST_CHANGED_LOG}")
	
	set (${PROJECT_NAME}_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH}.${Project_WC_REVISION})
	
ENDIF(Subversion_FOUND)