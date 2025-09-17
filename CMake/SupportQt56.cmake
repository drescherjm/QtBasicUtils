# Find Qt via vcpkg if not found fail hard!
find_package(QT NAMES ${SELECT_QT_VERSION} REQUIRED)

# The ability to support Qt5 or Qt6 is based on the following stackoverflow answer:
# https://stackoverflow.com/a/71131723/487892

#Create a variable containing Qt5 or Qt6
set(QT Qt${QT_VERSION_MAJOR})

set(${PROJECT_NAME}_QT_VERSION ${QT_VERSION_MAJOR})

if (${QT_VERSION_MAJOR} EQUAL 6)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	
	if(MSVC)
		#Qt6 requires these! 
		add_compile_options(/Zc:__cplusplus)
		add_compile_options(/permissive-)
	endif()
endif()