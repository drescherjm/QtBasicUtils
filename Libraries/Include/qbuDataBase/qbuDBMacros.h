#pragma once

#ifndef QBUDBMACROS_H
#define QBUDBMACROS_H

#include "qbuBase/qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////
/**
 *	\brief 
 *	This macro declares the superclass and sets up the copy constructors
 *	and assignment operators along with the copy() and destroy() 
 *	helpers.
 */

#define QBU_DECLARE_INFO_HELPERS(thisClass,baseClass) \
public: \
	QBU_DECLARE_SUPERCLASS(baseClass) \
	QBU_DECLARE_CONSTRUCTOR_DESTRUCTOR(thisClass) \
	QBU_DECLARE_CPY_ASGN_BASE_INCLUDED(thisClass) \
	QBU_DECLARE_CPY_ASGN_HELPERS(thisClass) \
public: \

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief 
 *	This macro implements the copy() and destroy() member functions for all qbuInfo 
 *  derived classes. 
 */

#define QBU_IMPLEMENT_INFO_COPY_DESTROY(thisClass) \
	void thisClass::copy(const thisClass & other) {} \
	\
	void thisClass::destroy() \
	{ \
		clear(); \
	} \

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief 
 *	This macro implements the copy constructors for the qbuInfo class derived classes.
 *	\note
 *	The code may look unusual but it is correct. The reason why we do not use the 
 *  standard copy constructor assignment is because this will cause a pure virtual
 *  call because the abstract base copy requires the derived class to exist.
 *
 */

#define QBU_IMPLEMENT_INFO_COPY_CONSTRUCTORS(thisClass) \
	thisClass::thisClass( const thisClass & other ) : Superclass() \
	{ \
		Superclass::copy(other); \
	} \
	\
	thisClass::thisClass( const Superclass & other ) : Superclass() \
	{ \
		Superclass::copy(other); \
	}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief 
*	This macro implements the assignment operators (operator=) for the qbuInfo class 
*	derived classes.
*/

#define QBU_IMPLEMENT_INFO_ASSIGNMENT_OPERATORS(thisClass) \
	thisClass& thisClass::operator=( const Superclass & other ) \
	{ \
		Superclass::operator =(other); \
		return *this; \
	} \
	QBU_IMPLEMENT_ASSIGNMENT_OPERATOR_DERIVED(thisClass,Superclass)

/////////////////////////////////////////////////////////////////////////////////////////

#define QBU_IMPLEMENT_INFO_CONSTRUCTOR_DESTRUCTOR(thisClass) \
	thisClass::thisClass() : Superclass() {} \
	\
	thisClass::~thisClass() \
	{ \
		destroy(); \
	}

/////////////////////////////////////////////////////////////////////////////////////////

#define QBU_IMPLEMENT_INFO_HELPERS(thisClass) \
	QBU_IMPLEMENT_INFO_ASSIGNMENT_OPERATORS(thisClass) \
	QBU_IMPLEMENT_INFO_COPY_DESTROY(thisClass) \
	QBU_IMPLEMENT_INFO_COPY_CONSTRUCTORS(thisClass)

/////////////////////////////////////////////////////////////////////////////////////////

#define QBU_IMPLEMENT_UPGRADE_DB_TABLE(thisClass, tableClass,tableName) \
	bool thisClass::upgrade##tableName( int nOldSchema, int nNewSchema ) \
	{ \
		bool retVal = isOpen(); \
		if (retVal) { \
			tableClass table(m_pPublic->shared_from_this()); \
			retVal = table.upgradeTable(nOldSchema,nNewSchema); \
		} \
		return retVal; \
	}

/////////////////////////////////////////////////////////////////////////////////////////

#define QBU_IMPLEMENT_VERIFY_DB_TABLE(thisClass, tableClass,tableName) \
	bool thisClass::verify##tableName##Schema( QString & strTableName ) \
	{ \
		tableClass table(m_pPublic->shared_from_this()); \
		strTableName = table.getTableName(); \
		return table.verifySchema(); \
	}

/////////////////////////////////////////////////////////////////////////////////////////

#define QBU_IMPLEMENT_ADD_DB_VIEW(thisClass, viewClass,viewName) \
	bool thisClass::add##viewName( int nOldSchema, int nNewSchema ) \
	{ \
		bool retVal = isOpen(); \
		if (retVal) { \
			viewClass view(m_pPublic->shared_from_this()); \
			retVal = view.upgradeDBView(nOldSchema,nNewSchema,true); \
		} \
		return retVal; \
	}

/////////////////////////////////////////////////////////////////////////////////////////

#define QBU_IMPLEMENT_DB_FIX_KNOWN_TABLE_PROBLEMS(thisClass, tableClass,tableName) \
	bool thisClass::fix##tableName() \
	{ \
		bool retVal = isOpen(); \
		if (retVal) { \
			tableClass table(m_pPublic->shared_from_this()); \
			retVal = table.fixKnownProblems(); \
		} \
		return retVal; \
	}

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBMACROS_H
