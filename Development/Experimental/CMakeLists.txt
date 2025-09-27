myproject(Experimental)

include_directories(
	Include 
	../Include
	${${PROJECT_NAME}_INCLUDE_DIRS}
)

SET( ${LOCAL_PROJECT_NAME}_SRCS
	./src/xrvariant.cpp
	./src/xrbase64.cpp
	./src/main.cxx
)

SET( ${LOCAL_PROJECT_NAME}_HDRS 
	./Include/xrvariant.h
	./Include/xrbase64.h
	
)

SET( ${LOCAL_PROJECT_NAME}_MOC_HDRS 

)

# and finally this will run moc:
QT45_WRAP_CPP( ${LOCAL_PROJECT_NAME}_MOC_SRCS ${${LOCAL_PROJECT_NAME}_MOC_HDRS} )

add_executable(${LOCAL_PROJECT_NAME} ${${LOCAL_PROJECT_NAME}_SRCS} 
    ${${LOCAL_PROJECT_NAME}_MOC_SRCS} 
	${${LOCAL_PROJECT_NAME}_HDRS}
	${${LOCAL_PROJECT_NAME}_MOC_HDRS}
)

target_link_libraries(${LOCAL_PROJECT_NAME} PRIVATE ${QT_LIBRARIES} qbuBase )

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES FOLDER Development)