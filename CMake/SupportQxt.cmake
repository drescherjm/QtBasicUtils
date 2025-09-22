function (SupportQxt)
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
				
		print_list("QXT_LIBRARIES=" ${QXT_LIBRARIES})
		
		# The following line is necissary because append_unique() will bring the variable
		# into the local scope. 
		set(QXT_LIBRARIES "${QXT_LIBRARIES}" PARENT_SCOPE)
		
	else()
		include(${PROJECT_SOURCE_DIR}/CMake/External/Scripts/GetQxtRuntime.cmake)
	endif()	
endfunction()