
FIND_PACKAGE( Qt4 REQUIRED )

set(QT_USE_QTXML true)
INCLUDE( ${QT_USE_FILE} )

include_directories(
	Include 
	../Include
	${${PROJECT_NAME}_INCLUDE_DIRS}
)

link_directories(../bin)

SET( EXPERIMENTAL_SRCS
	./src/xrvariant.cpp
	./src/xrbase64.cpp
	./src/main.cxx
)

SET( EXPERIMENTAL_HDRS 
	./Include/xrvariant.h
	./Include/xrbase64.h
	
)

SET( EXPERIMENTAL_MOC_HDRS 

)

# and finally this will run moc:
QT4_WRAP_CPP( EXPERIMENTAL_MOC_SRCS ${EXPERIMENTAL_MOC_HDRS} )

add_executable(experimental ${EXPERIMENTAL_SRCS} 
    ${EXPERIMENTAL_MOC_SRCS} 
	${EXPERIMENTAL_HDRS}
	${EXPERIMENTAL_MOC_HDRS}
)

target_link_libraries(experimental  ${QT_LIBRARIES} ${${PROJECT_NAME}_LIBRARIES} )
