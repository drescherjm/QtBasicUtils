function (SupportQxt)
	
	set(options DEBUG)
	set(oneValueArgs "")
    set(multiValueArgs "")
	
	cmake_parse_arguments( arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
	
	find_package(libQxt REQUIRED)
	if (libQxt_FOUND) 
		if (NOT QXT_LIBRARIES) 
			set(QXT_LIBRARIES "" PARENT_SCOPE)
		endif()
	
		foreach(module ${QXT_FIND_COMPONENTS})
			if (NOT TARGET Qxt::${module}) 
				find_package(libQxt COMPONENTS ${module} )
				if (NOT TARGET Qxt::${module}) 
					message(FATAL_ERROR "Could not find Qxt::${module}")
				endif()
			endif()		
			
			append_unique(QXT_LIBRARIES Qxt::${module})
		endforeach()
				
		# Add some debugging info about the targets!
		if (arg_DEBUG)
			print_list("Processing: ${CMAKE_PARENT_LIST_FILE}\n-- QXT_LIBRARIES=" ${QXT_LIBRARIES})
			
			include(CMakePrintHelpers)
			
			cmake_print_properties(
				TARGETS ${QXT_LIBRARIES}
				PROPERTIES
					INTERFACE_INCLUDE_DIRECTORIES
					INTERFACE_LINK_LIBRARIES
					LINK_LIBRARIES
					INTERFACE_COMPILE_DEFINITIONS
					LOCATION
			)
		endif()
		
		# The following line is necissary because append_unique() will bring the variable
		# into the local scope. 
		set(QXT_LIBRARIES "${QXT_LIBRARIES}" PARENT_SCOPE)
		
	else()
		include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/GetQxtRuntime.cmake)
	endif()	
endfunction()