#########################################################################################

macro( MSVC_PCH_SUPPORT ProjectName )
if (MSVC)
	if (USE_MSVC_PCH)
	
		set_source_files_properties(${ProjectName}PCH.cxx
			PROPERTIES
			COMPILE_FLAGS "/Yc${ProjectName}PCH.h"
			)
		foreach( src_file ${${ProjectName}_SRCS} )
			set_source_files_properties(
				${src_file}
				PROPERTIES
				COMPILE_FLAGS "/Yu${ProjectName}PCH.h"
				)
		endforeach( src_file ${${ProjectName}_SRCS} )
		
		list(APPEND ${ProjectName}_SRCS ${ProjectName}PCH.cxx)
		list(APPEND ${ProjectName}_EXT_HDRS ${ProjectName}PCH.h)

	endif(USE_MSVC_PCH)
endif (MSVC)
endmacro (MSVC_PCH_SUPPORT)