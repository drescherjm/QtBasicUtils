function (SupportQxt)
	if (NOT TARGET QxtCore) 
		find_package(libQxt REQUIRED)
	endif()
	
	include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/GetQxtRuntime.cmake)
endfunction()