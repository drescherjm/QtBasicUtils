#########################################################################################
# This module allows the checking of 64 bit portability on 32 bit visual studio builds
#########################################################################################

if(CMAKE_SIZEOF_VOID_P MATCHES 4)
	option (DETECT_64BIT_PORTABILITY 	"Warn on portability issues for 64 bit compiles" ON)
	IF(DETECT_64BIT_PORTABILITY)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wp64")
	ENDIF(DETECT_64BIT_PORTABILITY)
endif(CMAKE_SIZEOF_VOID_P MATCHES 4)