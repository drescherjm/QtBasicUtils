#include "qbuDBBasePCH.h"
#include "qbuDBColumnDef.h"
#include "qbuDatabaseFunctions.h"

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBColDef::getNameOrAlias() const
{
	QString retVal = m_strAlias;
	if (retVal.isEmpty()) {
		retVal = m_strName;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBColDef::getFullString() const
{
	QString retVal = getFullName();
	if (!m_strAlias.isEmpty()) {
		retVal.append(" AS ");
		retVal.append(m_strAlias);
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef::qbuDBColDef( QString strFieldName, QString strAlias ) : 
    m_strName(singleQuoteIfNecissary(strFieldName)),
	m_strAlias(singleQuoteIfNecissary(strAlias))
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef::qbuDBColDef( QString strFieldName, bool bAutoQuote ) 
{
	addNameInt(strFieldName,bAutoQuote);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef::qbuDBColDef( const qbuDBColDef & other )
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	Returns a new qbuDBColDef containing a copy of this object with the TableAlias
 *  set from the param strTableAlias.
 */

qbuDBColDef qbuDBColDef::addTableAlias( QString strTableAlias ) const
{
	qbuDBColDef retVal(*this);
	retVal.m_strTableAlias = singleQuoteIfNecissary(strTableAlias);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	Returns a new qbuDBColDef containing a copy of this object with the Alias
*   set from the param strAlias.
*/

qbuDBColDef qbuDBColDef::addAlias( QString strAlias ) const
{
	qbuDBColDef retVal(*this);
	retVal.m_strAlias = singleQuoteIfNecissary(strAlias);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	Returns a new qbuDBColDef containing a copy of this object with the Name
*   set from the param strName.
*/

qbuDBColDef qbuDBColDef::addName(QString strName, bool bAutoQuote/* =true */ ) const
{
	qbuDBColDef retVal(*this);
	retVal.addNameInt(strName,bAutoQuote);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBColDef::copy( const qbuDBColDef & other )
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

QString qbuDBColDef::getFullName() const
{
	QString retVal = m_strName;
	if (!m_strTableAlias.isEmpty()) {
		retVal.prepend(m_strTableAlias+".");
	}
	return retVal;

}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBColDef::getNameOnly() const
{
	QString retVal = m_strName;
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef& qbuDBColDef::operator=( const qbuDBColDef other )
{
	if ( &other != this ) {
		copy(other);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef qbuDBColDef::addExpression( QString strExpression ) const
{
	return addName(strExpression,false);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBColDef::addNameInt( QString strName,bool bAutoQuote )
{
	if (bAutoQuote) {
		m_strName = singleQuoteIfNecissary(strName);
	}
	else
	{
		m_strName = strName;
	}
}

