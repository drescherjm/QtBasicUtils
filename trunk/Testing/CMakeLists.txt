
include_directories( 
	${PROJECT_BINARY_DIR} 
	${PROJECT_BINARY_DIR}/.. 
	${PROJECT_SOURCE_DIR}/Include 
	./Include
	${${PROJECT_NAME}_INCLUDE_DIRS}
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
target_link_libraries(BasicTest ${${PROJECT_NAME}_LIBRARIES} ${QT_LIBRARIES})

add_dependencies(BasicTest ${${PROJECT_NAME}_LIBRARIES})

Include(UnitTests.cmake)