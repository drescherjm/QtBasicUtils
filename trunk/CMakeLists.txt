PROJECT(QtBasicUtils)

CMAKE_MINIMUM_REQUIRED (VERSION 2.6 FATAL_ERROR)

option (BUILD_TESTING "Build Tests" ON)

SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")

FIND_PACKAGE( Qt4 REQUIRED )
INCLUDE( ${QT_USE_FILE} )

IF(WIN32)
    SET(CMAKE_CXX_FLAGS "/WL /GR /EHsc" ) 
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
	
	IF(MSVC90)
		SET(CMAKE_DEBUG_POSTFIX "_d_2008")
		SET(CMAKE_RELEASE_POSTFIX "_2008")
	ENDIF(MSVC90)
	
	IF(MSVC80)
		SET(CMAKE_DEBUG_POSTFIX "_d_2005")
		SET(CMAKE_RELEASE_POSTFIX "_2005")
	ENDIF(MSVC80)
	
	IF(MSVC71)
		SET(CMAKE_DEBUG_POSTFIX "_d_2003")
		SET(CMAKE_RELEASE_POSTFIX "_2003")
	ENDIF(MSVC71)
	
	IF(MSVC70)
		SET(CMAKE_DEBUG_POSTFIX "_d_2002")
		SET(CMAKE_RELEASE_POSTFIX "_2002")
	ENDIF(MSVC70)
	
	IF(MSVC60)
		SET(CMAKE_DEBUG_POSTFIX "_d")
		SET(CMAKE_RELEASE_POSTFIX "_vc6")
	ENDIF(MSVC60)
	
ELSE(WIN32)
	SET(CMAKE_DEBUG_POSTFIX "_d")
ENDIF(WIN32)

set (QTBASICUTILS_VERSION_MAJOR 1)
set (QTBASICUTILS_VERSION_MINOR 0)

configure_file (
	"${PROJECT_SOURCE_DIR}/QtBasicUtilsConfig.h.in"
	"${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.h"
)

set (QTBASICUTILS_INCLUDE  ${CMAKE_INSTALL_PREFIX}/include )
set (QTBASICUTILS_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (QTBASICUTILS_RELEASE_LIB ${PROJECT_NAME} )
set (QTBASICUTILS_DEBUG_LIB ${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

configure_file (
	"${PROJECT_SOURCE_DIR}/QtBasicUtilsConfig.cmake.in"
	"${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.cmake"
)

export_library_dependencies (
	"${PROJECT_BINARY_DIR}/QtBasicUtilsLibraryDepends.cmake"
)

SET( QtBasicUtils_SRCS
	./src/main.cxx
	./src/QCmd.cxx
	./src/QCmdLine.cxx
	./src/QCmdPart.cxx
	./src/QCmdOpt.cxx
	./src/QCmdHelpException.cxx
	./src/QCmdParseException.cxx
	./src/QCmdParseError.cxx
	./src/QCmdOptBool.cxx
	./src/QCmdOptQChar.cxx
	./src/QCmdOptQString.cxx
	./src/QCmdOptQStringList.cxx
	./src/QCmdArg.cxx
	./src/QCmdArgBool.cxx
	./src/QCmdArgQChar.cxx
	./src/QCmdArgQString.cxx
	./src/QCmdArgQStringList.cxx
	./src/QCmdArgFileList.cxx
	./src/QCmdLineFileList.cxx
	./src/QCmdHelp.cxx
)

SET( QtBasicUtils_EXT_HDRS 
	./include/QtBasicUtils.h
	./include/QLimits.h
	./include/QCmd.h
	./include/QCmdLine.h
	./include/QCmdExtra.h
	./include/QCmdParseError.h
	./include/QCmdHelpException.h
	./include/QCmdParseException.h
	./include/QCmdLineFileList.h
	./include/QCmdPart.h
	./include/QCmdArg.h
	./include/QCmdOpt.h
	./include/QCmdOptBasicBase.h
	./include/QCmdOptBasicBase.txx
	./include/QCmdOptBasicBaseMM.h
	./include/QCmdOptBasicBaseMM.txx
	./include/QCmdOptBasic.h
	./include/QCmdOptBasic.txx
	./include/QCmdOptBool.h
	./include/QCmdOptQChar.h
	./include/QCmdOptQString.h
	./include/QCmdOptQStringList.h
	./include/QCmdArgBool.h
	./include/QCmdArgBasic.h
	./include/QCmdArgBasic.txx
	./include/QCmdArgBasicBase.h
	./include/QCmdArgBasicBase.txx
	./include/QCmdArgBasicBaseMM.h
	./include/QCmdArgBasicBaseMM.txx
	./include/QCmdArgQChar.h
	./include/QCmdArgQString.h
	./include/QCmdArgQStringList.h
	./include/QCmdArgFileList.h
	./include/QCmdHelp.h
)

SET( QtBasicUtils_INT_HDRS
	"${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.h"
)

IF(BUILD_TESTING)
	ENABLE_TESTING()
	LINK_LIBRARIES(BasicTest QtBasicUtils ${QT_LIBRARIES})
	add_executable(BasicTest ./src/Tests/basic.cxx)
	ADD_TEST(Test0			${EXECUTABLE_OUTPUT_PATH}/BasicTest +?)
	ADD_TEST(Test1			${EXECUTABLE_OUTPUT_PATH}/BasicTest +Test 1.0)
	ADD_TEST(StringListArg0  ${EXECUTABLE_OUTPUT_PATH}/BasicTest +STRLSTARG 1 2 3 4 . -S10)
	ADD_TEST(StringListArg1  ${EXECUTABLE_OUTPUT_PATH}/BasicTest +STRLSTARG 1 2 3 . -S6)
	ADD_TEST(StringListOpt0  ${EXECUTABLE_OUTPUT_PATH}/BasicTest +STRLSTOPT -I1 2 3 . -S6)
	ADD_TEST(StringListOpt1  ${EXECUTABLE_OUTPUT_PATH}/BasicTest +STRLSTOPT -I1 2 3 4 . -S10)
		
ENDIF(BUILD_TESTING)


include_directories( ${PROJECT_BINARY_DIR} ${PROJECT_BINARY_DIR}/.. ${PROJECT_SOURCE_DIR}/include )

add_library(QtBasicUtils ${QtBasicUtils_SRCS} ${QtBasicUtils_EXT_HDRS} ${QtBasicUtils_INT_HDRS} )

install (FILES
	${PROJECT_BINARY_DIR}/QtBasicUtilsConfig.cmake
	${PROJECT_BINARY_DIR}/QtBasicUtilsLibraryDepends.cmake
	${PROJECT_SOURCE_DIR}/QtBasicUtilsUse.cmake
	DESTINATION lib
)

install (TARGETS QtBasicUtils DESTINATION lib)
install (FILES ${QtBasicUtils_EXT_HDRS} DESTINATION include)


