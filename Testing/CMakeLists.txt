
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
	./src/testxmlperf.cxx
	./src/testDBExpression.cxx
	./src/testDBCaseStatement.cxx
)

set(TEST_HDRS
	./Include/testxml.h
	./Include/testxmlimp.h
	./Include/testUserProps.h
	./Include/testCommandLineInclude.h
	./Include/testSetVariable.h
	./Include/cmdTestFloatOpts.h
	./Include/testxmlperf.h
	./Include/testDBExpression.h
	./Include/testDBCaseStatement.h
)

add_executable(BasicTest ${TEST_SRCS} ${TEST_HDRS})
target_link_libraries(BasicTest ${${PROJECT_NAME}_LIBRARIES} ${QT_LIBRARIES})

target_link_libraries(BasicTest qbu::qbuDataBase)

add_dependencies(BasicTest ${${PROJECT_NAME}_LIBRARIES})

Include(UnitTests.cmake)