LINK_LIBRARIES(BasicTest QtBasicUtils ${QT_LIBRARIES})

include_directories( 
	${PROJECT_BINARY_DIR} 
	${PROJECT_BINARY_DIR}/.. 
	${PROJECT_SOURCE_DIR}/Include 
	./Include
)

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
	./Include/testxml.h
	./Include/testxmlimp.h
	./Include/testUserProps.h
	./Include/testCommandLineInclude.h
	./Include/testSetVariable.h
	./Include/cmdTestFloatOpts.h
)

add_executable(BasicTest ${TEST_SRCS} ${TEST_HDRS})

add_dependencies(BasicTest QtBasicUtils)

Include(UnitTests.cmake)