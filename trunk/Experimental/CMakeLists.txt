
FIND_PACKAGE( Qt4 REQUIRED )

set(QT_USE_QTXML true)
INCLUDE( ${QT_USE_FILE} )

include_directories(include)

SET( EXPERIMENTAL_SRCS
	./src/xrvariant.cpp
	./src/xrbase64.cpp
)

SET( EXPERIMENTAL_HDRS 
	./include/xrvariant.h
	./include/xrbase64.h
)

add_executable(experimental ${EXPERIMENTAL_SRCS} ${EXPERIMENTAL_HDRS})
