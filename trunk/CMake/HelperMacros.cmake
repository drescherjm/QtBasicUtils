#########################################################################################
#
#	This module contains a few Helper Macros that add case insensitive list operations
#	among other functionality.
#
#########################################################################################

MACRO(LIST_CONTAINS var value)
  SET(${var})
  FOREACH (value2 ${ARGN})
    IF (${value} STREQUAL ${value2})
      SET(${var} TRUE)
	  break()
    ENDIF (${value} STREQUAL ${value2})
  ENDFOREACH (value2)
ENDMACRO(LIST_CONTAINS)

#########################################################################################

MACRO(LIST_CONTAINS_IGNORE_CASE var value)
  SET(${var})
  FOREACH (value2 ${ARGN})
    IF (${value} STREQUAL ${value2})
      SET(${var} TRUE)
	ELSE(${value} STREQUAL ${value2})
		STRING( TOUPPER ${value} UpcaseValue )
		STRING( TOUPPER ${value2} UpcaseValue2 )
		 if (${UpcaseValue} STREQUAL ${UpcaseValue2})
			set(${var} TRUE)
			break()
		 endif (${UpcaseValue} STREQUAL ${UpcaseValue2})
    ENDIF (${value} STREQUAL ${value2})
  ENDFOREACH (value2)
ENDMACRO(LIST_CONTAINS_IGNORE_CASE)

#########################################################################################
# Returns ${value}-NOTFOUND if not found or the matched string in the same case as the 
# list

MACRO(LIST_FIND_IGNORE_CASE var value)
  SET(${var} "${value}-NOTFOUND")
  FOREACH (value2 ${ARGN})
    IF (${value} STREQUAL ${value2})
      SET(${var} ${value2})
	  break()
	ELSE(${value} STREQUAL ${value2})
		STRING( TOUPPER ${value} UpcaseValue )
		STRING( TOUPPER ${value2} UpcaseValue2 )
		 if (${UpcaseValue} STREQUAL ${UpcaseValue2})
			set(${var} ${value2})
			break()
		 endif (${UpcaseValue} STREQUAL ${UpcaseValue2})
    ENDIF (${value} STREQUAL ${value2})
  ENDFOREACH (value2)
ENDMACRO(LIST_FIND_IGNORE_CASE)

#########################################################################################

MACRO(LIST_FIND var value)
  SET(${var} "${value}-NOTFOUND")
  FOREACH (value2 ${ARGN})
    IF (${value} STREQUAL ${value2})
      SET(${var} ${value2})
	  break()
    ENDIF (${value} STREQUAL ${value2})
  ENDFOREACH (value2)
ENDMACRO(LIST_FIND)

#########################################################################################

macro(LIST_TO_CSV_STRING my_string)
	unset( ___TEMP___ )
	FOREACH (value2 ${ARGN})
		if (___TEMP___)
			set ( ___TEMP___ ${___TEMP___} "," ${value2} )
		else(___TEMP___)
			set ( ___TEMP___ ${value2} )
		endif(___TEMP___)
	ENDFOREACH (value2) 
	set( ${my_string} "${___TEMP___}" )
	unset( ___TEMP___ )
endmacro(LIST_TO_CSV_STRING)

#########################################################################################

macro( print_list my_message)
	unset(__LIST_OUTPUT__)
	LIST_TO_CSV_STRING( __LIST_OUTPUT__ ${ARGN} )
	MESSAGE( STATUS "${my_message} " ${__LIST_OUTPUT__})
	unset(__LIST_OUTPUT__)
endmacro( print_list )

#########################################################################################

macro( conditional_define VariableName DefineName)
	if (${VariableName})
	
		message( STATUS "add_definitions(-D${DefineName})" )
		add_definitions(-D${DefineName})
		
	endif(${VariableName})
endmacro( conditional_define )

#########################################################################################

macro( conditional_not_define VariableName DefineName)
	if (NOT ${VariableName})
	
		message( STATUS "add_definitions(-D${DefineName})" )
		add_definitions(-D${DefineName})
		
	endif(NOT ${VariableName})
endmacro( conditional_not_define )

#########################################################################################

function( define_from_environment VariableName PackageName)
	if (NOT DEFINED ${VariableName})
		message( STATUS "${VariableName}=$ENV{${VariableName}}" )
		if (NOT "$ENV{${VariableName}}" STREQUAL "")
			set(${VariableName} $ENV{${VariableName}} CACHE PATH "Set the path for ${PackageName}" FORCE)
		endif (NOT "$ENV{${VariableName}}" STREQUAL "")
	endif(NOT DEFINED ${VariableName})
endfunction( define_from_environment)

#########################################################################################

macro( myproject ProjectName )
	set( LOCAL_PROJECT_NAME ${ProjectName})
	set( LOCAL_PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
	set( LOCAL_PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
endmacro( myproject )

#########################################################################################

macro(create_string_from_list my_str)
 foreach(VALUE ${ARGN})
  if ("${VALUE}" STREQUAL "${ARGV1}")
   set(result "${VALUE}")
  else()
   set(result "${result} ${VALUE}")
  endif()
 endforeach(VALUE)
 set(${my_str} ${result})
endmacro(create_string_from_list) 
