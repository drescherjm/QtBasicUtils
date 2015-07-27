myproject(qbuGUIDev0)

include_directories(
	Include 
	../Include
	${${PROJECT_NAME}_INCLUDE_DIRS}
	${LOCAL_PROJECT_BINARY_DIR}
)

set( ${LOCAL_PROJECT_NAME}_SRCS
	./src/main.cxx
	./src/qbuGUIDev0MainWindow.cxx
	./src/DevelopGUIDB0.cxx
)

set( ${LOCAL_PROJECT_NAME}_HDRS 
	
)

set( ${LOCAL_PROJECT_NAME}_MOC_HDRS 
	./Include/qbuGUIDev0MainWindow.h
	./Include/DevelopGUIDB0.h
)

# and finally an resource file
set( ${LOCAL_PROJECT_NAME}_RCS
	
)

set( ${LOCAL_PROJECT_NAME}_UIS
	./rc/qbuGUIDev0MainWindow.ui
	./rc/DevelopGUIDB0.ui
)

# this command will generate rules that will run rcc on all files from ${LOCAL_PROJECT_NAME}_RCS
# in result ${LOCAL_PROJECT_NAME}_RC_SRCS variable will contain paths to files produced by rcc
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

add_executable(${LOCAL_PROJECT_NAME} ${${LOCAL_PROJECT_NAME}_SRCS} 
    ${${LOCAL_PROJECT_NAME}_MOC_SRCS} 
	${${LOCAL_PROJECT_NAME}_HDRS}
	${${LOCAL_PROJECT_NAME}_MOC_HDRS}
	${${LOCAL_PROJECT_NAME}_RCS}
	${${LOCAL_PROJECT_NAME}_UI_HDRS}
)

target_link_libraries(${LOCAL_PROJECT_NAME}  ${QT_LIBRARIES} ${${PROJECT_NAME}_LIBRARIES} )

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES FOLDER Development)