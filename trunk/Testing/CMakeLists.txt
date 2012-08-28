LINK_LIBRARIES(BasicTest QtBasicUtils ${QT_LIBRARIES})
include_directories( ${PROJECT_BINARY_DIR} ${PROJECT_BINARY_DIR}/.. ${PROJECT_SOURCE_DIR}/include ./include)

set(TEST_SRCS 
	./src/basic.cxx 
	./src/testxml.cxx
	./src/testxmlimp.cxx
	./src/testUserProps.cxx
	./src/testCommandLineInclude.cxx
	./src/testSetVariable.cxx
	./src/cmdTestFloatOpts.cxx
)

set(TEST_HDRS
	./include/testxml.h
	./include/testxmlimp.h
	./include/testUserProps.h
	./include/testCommandLineInclude.h
	./include/testSetVariable.h
	./Include/cmdTestFloatOpts.h
)

add_executable(BasicTest ${TEST_SRCS} ${TEST_HDRS})

add_dependencies(BasicTest QtBasicUtils)

include(UnitTests.cmake)