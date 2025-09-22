#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDBColumnDef.h"
#include "qbuDataBase/qbuDatabaseFunctions.h"
#include "qbuDataBase/qbuDBCondition.h"
#include "qbuLog/qbuLog.h"
#include "qbuDataBase/qbuDBExpression.h"
#include <QRegularExpression>

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

	if (m_options.testFlag(OP_DESCENDING)) {
		retVal.append(" DESC");
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef::qbuDBColDef(QString strFieldName, QString strAlias) :
m_strName(quoteSQLObjectNameIfNecessary(strFieldName)),
m_strAlias(quoteSQLObjectNameIfNecessary(strAlias))
{
	QRegularExpression reg("^[TQV]+\\d+$");

	if (reg.match(strAlias).hasMatch()) {
		QString strMsg = QString("Suspicious use of the Alias parameter -n %1. It looks like a table alias instead.").arg(__FUNCTION__);
		QLOG_WARN() << QBULOG_DATABASE_TYPE  << strMsg;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef::qbuDBColDef(QString strFieldName, Options op) : m_options(op)
{
	addNameInt(strFieldName);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef::qbuDBColDef(const qbuDBColDef & other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef::qbuDBColDef(const qbuDBCondition & expr, QString strAlias)
{
	m_strName = expr.toString();
	m_strAlias = quoteSQLObjectNameIfNecessary(strAlias);
    m_options = OP_IS_EXPRESSION;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef::qbuDBColDef()
{
	m_options = OP_NO_CODE;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef::qbuDBColDef(const qbuDBExpression & expr, QString strAlias)
{
	m_strName = expr.toString();
	m_strAlias = quoteSQLObjectNameIfNecessary(strAlias);
	m_options = OP_IS_EXPRESSION;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	Returns a new qbuDBColDef containing a copy of this object with the TableAlias
*  set from the param strTableAlias.
*/

qbuDBColDef qbuDBColDef::addTableAlias(QString strTableAlias) const
{
	qbuDBColDef retVal(*this);
	retVal.setTableAlias(strTableAlias);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	Returns a new qbuDBColDef containing a copy of this object with the Alias
*   set from the param strAlias.
*/

qbuDBColDef qbuDBColDef::addAlias(QString strAlias) const
{
	qbuDBColDef retVal(*this);
	retVal.setAlias(strAlias);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	Returns a new qbuDBColDef containing a copy of this object with the Name
*   set from the param strName.
*/

qbuDBColDef qbuDBColDef::addName(QString strName, Options op/* =true */) const
{
	qbuDBColDef retVal(*this);
	retVal.m_options = op;
	retVal.addNameInt(strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBColDef::copy(const qbuDBColDef & other)
{
	m_strName = other.m_strName;
	m_strAlias = other.m_strAlias;
	m_strTableAlias = other.m_strTableAlias;
	m_options = other.m_options;
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
		retVal.prepend(m_strTableAlias + ".");
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

qbuDBColDef& qbuDBColDef::operator=(const qbuDBColDef other)
{
	if (&other != this) {
		copy(other);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBColDef qbuDBColDef::addExpression(QString strExpression) const
{
	return addName(strExpression, OP_IS_EXPRESSION);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBColDef::addNameInt(QString strName)
{
	if (m_options.testFlag(OP_AUTO_QUOTE)) {
		m_strName = quoteSQLObjectNameIfNecessary(strName);
	}
	else
	{
		m_strName = strName;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBColDef::isExpression() const
{
	return m_options.testFlag(OP_IS_EXPRESSION);
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBColDef::getAlias() const
{
	return m_strAlias;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBColDef::hasAlias() const
{
	return !getAlias().isEmpty();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBColDef::setTableAlias(QString strTableAlias)
{
	m_strTableAlias = quoteSQLObjectNameIfNecessary(strTableAlias);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBColDef::setAlias(QString strAlias)
{
	m_strAlias = quoteSQLObjectNameIfNecessary(strAlias);
}

/////////////////////////////////////////////////////////////////////////////////////////
