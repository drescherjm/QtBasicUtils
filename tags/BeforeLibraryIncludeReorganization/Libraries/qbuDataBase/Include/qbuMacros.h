#ifndef __QBUMACROS_H__
#define __QBUMACROS_H__
#pragma warning( error : 4706)

/////////////////////////////////////////////////////////////////////////////////////////

/** 
 * 	Creates a public typedef for the base class as Superclass.
 */
#define QBU_DECLARE_SUPERCLASS(superclassName) \
public: \
	typedef superclassName Superclass;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This macro defies the default constructor and destructor for a class. 
 */

#define QBU_DECLARE_CONSTRUCTOR_DESTRUCTOR(thisClass) \
public: \
	thisClass(); \
	~thisClass();

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	Declare standard copy constructor and assignment operators
 */
#define QBU_DECLARE_CPY_ASGN(className) \
	className( const className & other ); \
	className& operator=( const className & other ); 

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	Declare standard copy constructor and assignment operators for this class and
 *  also base class assignment.
 */
#define QBU_DECLARE_CPY_ASGN_BASE_INCLUDED(className) \
	className( const className & other ); \
	className& operator=( const className & other ); \
	className( const Superclass & other ); \
	className& operator=( const Superclass & other ); 


/////////////////////////////////////////////////////////////////////////////////////////

/**
*	Declare private helper functions for copy constructor and assignment operator
*/
#define QBU_DECLARE_CPY_ASGN_HELPERS(className) \
private: \
	void copy(const className & other); \
	void destroy(); 

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	Implement the assignment operator in a base class
 */
#define QBU_IMPLEMENT_ASSIGNMENT_OPERATOR_BASE(className) \
	className& className::operator=( const className & other ) \
{ \
	if ( this != &other ) { \
		destroy(); \
		copy(other); \
	} \
	return ( *this ); \
} 

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	Implement the assignment operator in a derived class
 */

#define QBU_IMPLEMENT_ASSIGNMENT_OPERATOR_DERIVED(className,baseClass) \
	className& className::operator=( const className & other ) \
{ \
	if ( this != &other ) { \
		destroy(); \
		baseClass::operator=(other); \
		copy(other); \
	} \
	return ( *this ); \
} 

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	Implement the standard copy constructor in a base class.
 */
#define QBU_IMPLEMENT_COPY_CONSTRUCTOR_BASE(className) \
	className::className( const className & other ) \
{ \
	copy(other); \
} 

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	Implement the standard copy constructor in a derived class.
*/
#define QBU_IMPLEMENT_COPY_CONSTRUCTOR_DERIVED(className,baseClass) \
	className::className( const className & other ) : baseClass(other) \
{ \
	copy(other); \
} 

/////////////////////////////////////////////////////////////////////////////////////////

#define QBU_IMPLEMENT_SET_PRIVATE(className,methodName,variableName, variableType) \
	bool className::set##methodName( variableType variableName ) \
	{ \
		bool retVal = (m_pPrivate != NULL); \
		if (retVal) { \
			m_pPrivate->m_##variableName = variableName; \
		} \
		return retVal; \
	}

/////////////////////////////////////////////////////////////////////////////////////////

#define QBU_IMPLEMENT_GET_PRIVATE(className,methodName,variableName, variableType) \
	bool className::get##methodName( variableType & variableName ) \
	{ \
		bool retVal = (m_pPrivate != NULL); \
		if (retVal) { \
			variableName = m_pPrivate->m_##variableName; \
		} \
		return retVal; \
	}

/////////////////////////////////////////////////////////////////////////////////////////

#define QBU_IMPLEMENT_GET_PRIVATE_CONST(className,methodName,variableName, variableType) \
	bool className::get##methodName( variableType & variableName ) const \
	{ \
	bool retVal = (m_pPrivate != NULL); \
	if (retVal) { \
	variableName = m_pPrivate->m_##variableName; \
	} \
	return retVal; \
	}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QBUMACROS_H__
