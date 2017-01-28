myproject(qbuLog)

init_lib_shared_static_option(OFF)

set(Boost_ADDITIONAL_VERSIONS "1.62" "1.62.0" "1.60" "1.60.0")
find_package( Boost REQUIRED )

include_directories( ${Boost_INCLUDE_DIRS} )

set (${LOCAL_PROJECT_NAME}_INSTALL_INCLUDE  ${CMAKE_INSTALL_PREFIX}/Include )
set (${LOCAL_PROJECT_NAME}_INSTALL_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (${LOCAL_PROJECT_NAME}_INSTALL_RELEASE_LIB ${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_INSTALL_DEBUG_LIB ${LOCAL_PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

set (${LOCAL_PROJECT_NAME}_TREE_INCLUDE  ${${PROJECT_NAME}_SRC_INCLUDE_DIR}/${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_TREE_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set (${LOCAL_PROJECT_NAME}_TREE_RELEASE_LIB ${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_TREE_DEBUG_LIB ${LOCAL_PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

set( ${LOCAL_PROJECT_NAME}_SRCS
	./src/qbuLog.cxx
	./src/qbuFileLoggerEngine.cxx
	./src/qbuFilteredFileLoggerEngine.cxx
	./src/qbuLoggerWidget.cxx
	./src/qbuLoggerModel.cxx
	./src/qbuLogModelEngine.cxx
	./src/qbuLoggerWidget2.cxx
	./src/qbuLoggerWidget2FileNameDelagate.cxx
	./src/qbuLoggerWidget3.cxx
)

set( ${LOCAL_PROJECT_NAME}_EXT_HDRS 
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuLog.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuFileLoggerEngine.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuFilteredFileLoggerEngine.h
)

set( ${LOCAL_PROJECT_NAME}_MOC_HDRS 
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuLoggerWidget.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuLoggerModel.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuLogModelEngine.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuLoggerWidget2.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuLoggerWidget2FileNameDelagate.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuLoggerWidget3.h
)

# some .ui files
set( ${LOCAL_PROJECT_NAME}_UIS
	./rc/qbuLoggerWidget2.ui
)

# and finally an resource file
set( ${LOCAL_PROJECT_NAME}_RCS
	./rc/qbuLog.qrc
)

set( ${LOCAL_PROJECT_NAME}_INT_HDRS

)

#Add precompiled header support
MSVC_PCH_SUPPORT(${LOCAL_PROJECT_NAME})

# this command will generate rules that will run rcc on all files from UPMC_LA_RCS
# in result UPMC_LA_RC_SRCS variable will contain paths to files produced by rcc
QT45_ADD_RESOURCES( ${LOCAL_PROJECT_NAME}_RC_SRCS ${${LOCAL_PROJECT_NAME}_RCS} )

# and finally this will run moc:
QT45_WRAP_CPP( ${LOCAL_PROJECT_NAME}_MOC_SRCS ${${LOCAL_PROJECT_NAME}_MOC_HDRS} )

# this will run uic on .ui files:
QT45_WRAP_UI( ${LOCAL_PROJECT_NAME}_UI_HDRS ${${LOCAL_PROJECT_NAME}_UIS} )

SOURCE_GROUP("Generated" FILES
	  ${${LOCAL_PROJECT_NAME}_RC_SRCS}
	  ${${LOCAL_PROJECT_NAME}_MOC_SRCS}
	  ${${LOCAL_PROJECT_NAME}_UI_HDRS}
)

SOURCE_GROUP("Resources" FILES
	  ${${LOCAL_PROJECT_NAME}_UIS}
	  ${${LOCAL_PROJECT_NAME}_RCS}
)

if(BUILD_DOCUMENTATION)

	ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR})
	ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/src)
	ADD_TO_DOC(${CMAKE_CURRENT_SOURCE_DIR}/Include)

endif(BUILD_DOCUMENTATION)


include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${PROJECT_BINARY_DIR} 
	${PROJECT_BINARY_DIR}/.. 
	${${PROJECT_NAME}_INCLUDE_DIRS}
)

add_library(${LOCAL_PROJECT_NAME} 
	${${LOCAL_PROJECT_NAME}_SRCS} 
	${${LOCAL_PROJECT_NAME}_EXT_HDRS} 
	${${LOCAL_PROJECT_NAME}_MOC_HDRS}
	${${LOCAL_PROJECT_NAME}_MOC_SRCS} 
	${${LOCAL_PROJECT_NAME}_INT_HDRS} 
	${${LOCAL_PROJECT_NAME}_UI_HDRS}
	${${LOCAL_PROJECT_NAME}_RC_SRCS}
)

#########################################################################################

if (BUILD_${LOCAL_PROJECT_NAME}_SHARED)
	target_link_libraries ( 
		${LOCAL_PROJECT_NAME} 
		${UPMC_EXTERNAL_LIBS} 
		${QT_LIBRARIES} 
		${QXT_LIBRARIES}
	)

	#########################################################################################

	install(TARGETS ${LOCAL_PROJECT_NAME}
	   RUNTIME
	   DESTINATION bin
	   COMPONENT Applications
	)
endif()

#########################################################################################

# install (FILES
	# ${LOCAL_PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}Config.cmake
	# ${LOCAL_PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}LibraryDepends.cmake
	# ${LOCAL_PROJECT_SOURCE_DIR}/${LOCAL_PROJECT_NAME}Use.cmake
	# DESTINATION lib
# )

#########################################################################################

GENERATE_EXPORT_HEADER( ${LOCAL_PROJECT_NAME} 
	BASE_NAME ${LOCAL_PROJECT_NAME}
	EXPORT_MACRO_NAME ${LOCAL_PROJECT_NAME}_EXPORT
	EXPORT_FILE_NAME "${LOCAL_PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}LibraryDefines.h"
	STATIC_DEFINE ${LOCAL_PROJECT_NAME}_STATIC
)

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES FOLDER Libraries)

install (TARGETS ${LOCAL_PROJECT_NAME} DESTINATION lib)
install (FILES ${${LOCAL_PROJECT_NAME}_EXT_HDRS} ${${LOCAL_PROJECT_NAME}_MOC_HDRS} DESTINATION include)

set (${PROJECT_NAME}_LIBRARIES ${${PROJECT_NAME}_LIBRARIES} ${LOCAL_PROJECT_NAME} PARENT_SCOPE)


