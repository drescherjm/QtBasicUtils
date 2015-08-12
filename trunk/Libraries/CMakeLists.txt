add_subdirectory(src)

# Propagate the libraries to the parent scope
set (${PROJECT_NAME}_LIBRARIES ${${PROJECT_NAME}_LIBRARIES} PARENT_SCOPE)
set (${PROJECT_NAME}_DEFINES ${${PROJECT_NAME}_DEFINES} PARENT_SCOPE)

#message( STATUS ${${PROJECT_NAME}_DEFINES} )