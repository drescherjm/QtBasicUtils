#########################################################################################

## Initialize the list.
SET( DOXYGEN_SOURCE_DIR "" CACHE INTERNAL "List of folders to add to the documentation.")

MACRO(ADD_TO_DOC FOLDER_TO_ADD_TO_DOCS)
     SET( DOXYGEN_SOURCE_DIR ${DOXYGEN_SOURCE_DIR} ${FOLDER_TO_ADD_TO_DOCS} CACHE INTERNAL "List of folders to add to the documentation.")
ENDMACRO(ADD_TO_DOC)

#########################################################################################

MACRO(ADD_TO_DISTCLEAN TARGET_TO_DELETE)
     SET( FILES_TO_DELETE ${FILES_TO_DELETE} ${TARGET_TO_DELETE} )
ENDMACRO(ADD_TO_DISTCLEAN)

#########################################################################################

# Create a "make doc" target using Doxygen
# Prototype:
#     GENERATE_DOCUMENTATION(doxygen_config_file)
# Parameters:

# doxygen_config_file Doxygen configuration file (must in root/doxygen of the source directory) 

MACRO(GENERATE_DOCUMENTATION DOXYGEN_CONFIG_FILE)
FIND_PACKAGE(Doxygen REQUIRED)
SET(DOXYFILE_FOUND false)
IF(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_CONFIG_FILE})
    SET(DOXYFILE_FOUND true)
ENDIF(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_CONFIG_FILE})

IF( DOXYGEN_FOUND )
    IF( DOXYFILE_FOUND )
        # Add target

	ADD_CUSTOM_TARGET( documentation ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_CONFIG_FILE}" > "${CMAKE_CURRENT_BINARY_DIR}/doxygen.log" )

	# Add .tag file and generated documentation to the list of files we must erase when distcleaning

        # Read doxygen configuration file

	message( STATUS "Doxygen Config file= " ${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_CONFIG_FILE} )
	FILE( READ ${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_CONFIG_FILE} DOXYFILE_CONTENTS )

        STRING( REGEX REPLACE "\n" ";" DOXYFILE_LINES ${DOXYFILE_CONTENTS} )

        # Parse .tag filename and add to list of files to delete if it exists
        FOREACH( DOXYLINE ${DOXYFILE_CONTENTS} )

			STRING( REGEX REPLACE ".*GENERATE_TAGFILE *= *([^ ^\n]+).*" "\\1" DOXYGEN_TAG_FILE ${DOXYLINE} )

        ENDFOREACH( DOXYLINE )
        ADD_TO_DISTCLEAN( ${PROJECT_BINARY_DIR}/${DOXYGEN_TAG_FILE} )


		# Parse doxygen output doc dir and add to list of files to delete if it exists

        FOREACH( DOXYLINE ${DOXYFILE_CONTENTS} )

			STRING( REGEX REPLACE ".*OUTPUT_DIRECTORY *= *([^ ^\n]+).*" "\\1" DOXYGEN_DOC_DIR ${DOXYLINE} )

        ENDFOREACH( DOXYLINE )
        ADD_TO_DISTCLEAN( ${PROJECT_BINARY_DIR}/${DOXYGEN_DOC_DIR} )
        ADD_TO_DISTCLEAN( ${PROJECT_BINARY_DIR}/${DOXYGEN_DOC_DIR}.dir )

    ELSE( DOXYFILE_FOUND )

MESSAGE( STATUS "Doxygen configuration file not found - Documentation will not be generated" )

    ENDIF( DOXYFILE_FOUND )
ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found - Documentation will not be generated")
ENDIF(DOXYGEN_FOUND)
ENDMACRO(GENERATE_DOCUMENTATION)
