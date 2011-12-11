#include "smDBBasePCH.h"
#include "smDBColumnDef.h"
#include "smDatabaseFunctions.h"

/////////////////////////////////////////////////////////////////////////////////////////

QString smDBColDef::getNameOrAlias() const
{
	QString retVal = m_strAlias;
	if (retVal.isEmpty()) {
		retVal = m_strName;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString smDBColDef::getFullString() const
{
	QString retVal = getFullName();
	if (!m_strAlias.isEmpty()) {
		retVal.append(" AS ");
		retVal.append(m_strAlias);
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

smDBColDef::smDBColDef( QString strFieldName, QString strAlias ) : 
    m_strName(singleQuoteIfNecissary(strFieldName)),
	m_strAlias(singleQuoteIfNecissary(strAlias))
{

}

/////////////////////////////////////////////////////////////////////////////////////////

smDBColDef::smDBColDef( QString strFieldName, bool bAutoQuote ) 
{
	addNameInt(strFieldName,bAutoQuote);
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBColDef::smDBColDef( const smDBColDef & other )
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	Returns a new smDBColDef containing a copy of this object with the TableAlias
 *  set from the param strTableAlias.
 */

smDBColDef smDBColDef::addTableAlias( QString strTableAlias ) const
{
	smDBColDef retVal(*this);
	retVal.m_strTableAlias = singleQuoteIfNecissary(strTableAlias);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	Returns a new smDBColDef containing a copy of this object with the Alias
*   set from the param strAlias.
*/

smDBColDef smDBColDef::addAlias( QString strAlias ) const
{
	smDBColDef retVal(*this);
	retVal.m_strAlias = singleQuoteIfNecissary(strAlias);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	Returns a new smDBColDef containing a copy of this object with the Name
*   set from the param strName.
*/

smDBColDef smDBColDef::addName(QString strName, bool bAutoQuote/* =true */ ) const
{
	smDBColDef retVal(*this);
	retVal.addNameInt(strName,bAutoQuote);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void smDBColDef::copy( const smDBColDef & other )
{
	m_strName = other.m_strName;
	m_strAlias = other.m_strAlias;
	m_strTableAlias = other.m_strTableAlias;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	Returns the string containing the name prepended with the table alias if it exists.
 *  An example of this is the following: T1.StudyID would be returned if the 
 *  name was set to StudyID and the TableAlias set to T1
 */

QString smDBColDef::getFullName() const
{
	QString retVal = m_strName;
	if (!m_strTableAlias.isEmpty()) {
		retVal.prepend(m_strTableAlias+".");
	}
	return retVal;

}

/////////////////////////////////////////////////////////////////////////////////////////

QString smDBColDef::getNameOnly() const
{
	QString retVal = m_strName;
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBColDef& smDBColDef::operator=( const smDBColDef other )
{
	if ( &other != this ) {
		copy(other);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBColDef smDBColDef::addExpression( QString strExpression ) const
{
	return addName(strExpression,false);
}

/////////////////////////////////////////////////////////////////////////////////////////

void smDBColDef::addNameInt( QString strName,bool bAutoQuote )
{
	if (bAutoQuote) {
		m_strName = singleQuoteIfNecissary(strName);
	}
	else
	{
		m_strName = strName;
	}
}

