myproject(qbuWidgets)

if(${PROJECT_NAME}_QT_VERSION VERSION_GREATER "4")
	set (QT_MODULES ${QT_MODULES} Qt5::Designer )
	
	find_qt5_packages()
endif()

set(QXT_FIND_COMPONENTS QxtCore, QxtGui)
set(QXT_USE_QXTCORE TRUE)
find_package(Qxt REQUIRED)
include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/GetQxtRuntime.cmake)

set (${LOCAL_PROJECT_NAME}_VERSION_MAJOR 1)
set (${LOCAL_PROJECT_NAME}_VERSION_MINOR 0)

set (${LOCAL_PROJECT_NAME}_INSTALL_INCLUDE  ${CMAKE_INSTALL_PREFIX}/Include )
set (${LOCAL_PROJECT_NAME}_INSTALL_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib )
set (${LOCAL_PROJECT_NAME}_INSTALL_RELEASE_LIB ${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_INSTALL_DEBUG_LIB ${LOCAL_PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

set (${LOCAL_PROJECT_NAME}_TREE_INCLUDE  ${${PROJECT_NAME}_INCLUDE_DIRS}/${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_TREE_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set (${LOCAL_PROJECT_NAME}_TREE_RELEASE_LIB ${LOCAL_PROJECT_NAME} )
set (${LOCAL_PROJECT_NAME}_TREE_DEBUG_LIB ${LOCAL_PROJECT_NAME}${CMAKE_DEBUG_POSTFIX} )

set( ${LOCAL_PROJECT_NAME}_SRCS
	./src/qbuWidgetsPlugin.cxx
	./src/qbuGroupBox.cxx
	./src/qbuGroupBoxInterface.cxx
	./src/qbuRadioButton.cxx
	./src/qbuRadioButtonInterface.cxx
	./src/qbuComboBox.cxx
	./src/qbuComboBoxInterface.cxx
	./src/qbuCheckBox.cxx
	./src/qbuCheckBoxInterface.cxx
)

set( ${LOCAL_PROJECT_NAME}_EXT_HDRS 
	
)

set( ${LOCAL_PROJECT_NAME}_MOC_HDRS 
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuWidgetsPlugin.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuGroupBox.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuGroupBoxInterface.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuRadioButton.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuRadioButtonInterface.h	
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuComboBox.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuComboBoxInterface.h	
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuCheckBox.h
	${${LOCAL_PROJECT_NAME}_TREE_INCLUDE}/qbuCheckBoxInterface.h	
)

# some .ui files
set( ${LOCAL_PROJECT_NAME}_UIS
)

# and finally an resource file
set( ${LOCAL_PROJECT_NAME}_RCS
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

add_library(${LOCAL_PROJECT_NAME} SHARED
	${${LOCAL_PROJECT_NAME}_SRCS} 
	${${LOCAL_PROJECT_NAME}_EXT_HDRS} 
	${${LOCAL_PROJECT_NAME}_MOC_HDRS}
	${${LOCAL_PROJECT_NAME}_MOC_SRCS} 
	${${LOCAL_PROJECT_NAME}_INT_HDRS} 
	${${LOCAL_PROJECT_NAME}_UI_HDRS}
	${${LOCAL_PROJECT_NAME}_RC_SRCS}
)

install (FILES
	${PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}Config.cmake
	${PROJECT_BINARY_DIR}/${LOCAL_PROJECT_NAME}LibraryDepends.cmake
	${PROJECT_SOURCE_DIR}/${LOCAL_PROJECT_NAME}Use.cmake
	DESTINATION lib
)

TARGET_LINK_LIBRARIES( ${LOCAL_PROJECT_NAME} ${QT_LIBRARIES} ${UPMC_EXTERNAL_LIBS} )

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES FOLDER Libraries)
set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES DEFINE_SYMBOL QDESIGNER_EXPORT_WIDGETS )

install (TARGETS ${LOCAL_PROJECT_NAME} DESTINATION lib)
install (FILES ${${LOCAL_PROJECT_NAME}_EXT_HDRS} ${${LOCAL_PROJECT_NAME}_MOC_HDRS} DESTINATION include)

#setup_qt_plugin( ${LOCAL_PROJECT_NAME} )


