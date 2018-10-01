myproject(qbuBase)

init_lib_shared_static_option(OFF)

# set (${LOCAL_PROJECT_NAME}_VERSION_MAJOR 1)
# set (${LOCAL_PROJECT_NAME}_VERSION_MINOR 0)

set (${LOCAL_PROJECT_NAME}_INSTALL_INCLUDE  ${CMAKE_INSTALL_PREFIX}/Include )
set (${LOCAL_PROJECT_NAME}_INSTALL_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (${LOCAL_PROJECT_NAME}_INSTALL_RELEASE_LIB ${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_INSTALL_DEBUG_LIB ${LOCAL_PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

set (${LOCAL_PROJECT_NAME}_TREE_INCLUDE  ${${PROJECT_NAME}_SRC_INCLUDE_DIR}/${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_TREE_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set (${LOCAL_PROJECT_NAME}_TREE_RELEASE_LIB ${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_TREE_DEBUG_LIB ${LOCAL_PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

set( ${LOCAL_PROJECT_NAME}_SRCS
	./src/qbuProperty.cxx
	./src/qbuPropertyMap.cxx
	./src/qbuPropertyTypeNameAlias.cxx
	./src/qbuUserProperty.cxx
	./src/qbuUserPropPtr.cxx
	./src/qbuPropertyList.cxx
	./src/qbuPropXMLHelper.cxx
	./src/qbuProperyMapXMLHelper.cxx
	./src/qbuITKIndent.cxx
	./src/qbuStringList.cxx
	./src/qbuObject.cxx
	./src/qbuException.cxx
	./src/qbuCSVModelWriter.cxx
	./src/qbuErrorBase.cxx
	./src/qbuState.cxx
	./src/qbuNonButtonCheckableSignal.cxx
	./src/qbuButtonSignalGroup.cxx
	./src/qbuButtonSignalBase.cxx
	./src/qbuButtonSignal.cxx
	./src/qbuThread.cxx
	./src/qbuThreadedQObjectDeleter.cxx
	./src/qbuWaitCursor.cxx
	./src/pugixml.cpp
	./src/qbuCheckBoxDelegate.cxx
	./src/qbuBooleanWidget.cxx
)

set( ${LOCAL_PROJECT_NAME}_EXT_HDRS 
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuMacros.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuUpdateTracker.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuPropXMLHelper.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuPropertyTypeNameAlias.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuProperyMapXMLHelper.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuNonThreadSafeSingleton.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuITKIndent.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuSleeperThread.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuException.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuErrorBase.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuThread.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuThreadedQObjectDeleter.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuWaitCursor.h
)

set( ${LOCAL_PROJECT_NAME}_MOC_HDRS 
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuProperty.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuPropertyMap.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuUserPropery.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuUserPropPtr.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuPropertyList.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuStringList.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuObject.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuCSVModelWriter.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuState.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuNonButtonCheckableSignal.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuButtonSignalGroup.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuButtonSignalBase.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuButtonSignal.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuCheckBoxDelegate.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuBooleanWidget.h
)

# some .ui files
set( ${LOCAL_PROJECT_NAME}_UIS
)

# and finally an resource file
set( ${LOCAL_PROJECT_NAME}_RCS
)

set( ${LOCAL_PROJECT_NAME}_INT_HDRS
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/pugiconfig.hpp
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/pugixml.hpp
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


message( STATUS ${${PROJECT_NAME}_INCLUDE_DIRS})

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
	TARGET_LINK_LIBRARIES ( 
		${LOCAL_PROJECT_NAME} 
		${UPMC_EXTERNAL_LIBS} 
		${QT_LIBRARIES} 
		${QXT_LIBRARIES}
	)

	install(TARGETS ${LOCAL_PROJECT_NAME}
	   RUNTIME
	   DESTINATION bin
	   COMPONENT Applications
	)

endif(BUILD_${LOCAL_PROJECT_NAME}_SHARED)

#########################################################################################

GENERATE_EXPORT_HEADER( ${LOCAL_PROJECT_NAME} 
	BASE_NAME ${LOCAL_PROJECT_NAME}
	EXPORT_MACRO_NAME ${LOCAL_PROJECT_NAME}_EXPORT
	EXPORT_FILE_NAME "${LOCAL_PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}LibraryDefines.h"
	STATIC_DEFINE ${LOCAL_PROJECT_NAME}_STATIC
)

#########################################################################################

# install (FILES
	# ${PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}Config.cmake
	# ${PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}LibraryDepends.cmake
	# ${PROJECT_SOURCE_DIR}/${LOCAL_PROJECT_NAME}Use.cmake
	# DESTINATION lib
# )

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES FOLDER Libraries)

install (TARGETS ${LOCAL_PROJECT_NAME} DESTINATION lib)

print_list( ${${LOCAL_PROJECT_NAME}_EXT_HDRS} )

install (FILES ${${LOCAL_PROJECT_NAME}_EXT_HDRS} ${${LOCAL_PROJECT_NAME}_MOC_HDRS} DESTINATION include)

#
set (${PROJECT_NAME}_LIBRARIES ${${PROJECT_NAME}_LIBRARIES} ${LOCAL_PROJECT_NAME} PARENT_SCOPE)


