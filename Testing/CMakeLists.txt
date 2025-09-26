myproject(BasicTest)


set(QXT_FIND_COMPONENTS QxtCore QxtGui)
set(QXT_USE_QXTCORE TRUE)
SupportQxt()

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

target_link_libraries(BasicTest PRIVATE ${QT_LIBRARIES} ${QXT_LIBRARIES})

target_link_libraries(BasicTest PRIVATE ${${PROJECT_NAME}_LIBRARY_PREFIX}::qbuDataBase ${${PROJECT_NAME}_LIBRARY_PREFIX}::qbuBase ${${PROJECT_NAME}_LIBRARY_PREFIX}::qbuCmdLine)

Include(UnitTests.cmake)

# In Qt6 we need to run windeployqt to setup the platform plugin and other plugins since this 
# doesn't happen automatically yet. With Qt5 this is not needed so just run for Qt6.
if (QT_VERSION_MAJOR EQUAL 6)
	if (MSVC) 
		add_custom_command(TARGET ${LOCAL_PROJECT_NAME} POST_BUILD
			COMMAND ${QT}::windeployqt --no-compiler-runtime \"$<TARGET_FILE:${LOCAL_PROJECT_NAME}>\"
			COMMENT "Running windeployqt for $<CONFIG>"
		)
	endif()
endif()
