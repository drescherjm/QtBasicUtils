
FIND_PACKAGE( Qt4 REQUIRED )

set(QT_USE_QTXML true)
INCLUDE( ${QT_USE_FILE} )

include_directories(include)

SET( EXPERIMENTAL_SRCS
	./src/xrvariant.cpp
	./src/xrbase64.cpp
	./src/Property.cxx
	./src/PropertyMap.cxx
	./src/main.cxx
)

SET( EXPERIMENTAL_HDRS 
	./include/xrvariant.h
	./include/xrbase64.h
	
)

SET( EXPERIMENTAL_MOC_HDRS 
	./include/Property.h
	./include/PropertyMap.h
)

# and finally this will run moc:
QT4_WRAP_CPP( EXPERIMENTAL_MOC_SRCS ${EXPERIMENTAL_MOC_HDRS} )

add_executable(experimental ${EXPERIMENTAL_SRCS} 
    ${EXPERIMENTAL_MOC_SRCS} 
	${EXPERIMENTAL_HDRS}
	${EXPERIMENTAL_MOC_HDRS}
)

target_link_libraries(experimental  ${QT_LIBRARIES} )
