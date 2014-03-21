add_subdirectory(src)

# Propagate the libraries to the parent scope
set (${PROJECT_NAME}_LIBRARIES ${${PROJECT_NAME}_LIBRARIES} PARENT_SCOPE)