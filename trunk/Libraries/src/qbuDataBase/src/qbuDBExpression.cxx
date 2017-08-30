#include "qbuDatabasePCH.h"

#include "qbuDataBase/qbuDBExpression.h"
#include "qbuDataBase/qbuDBColumnDef.h"
#include <memory>

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBExpression::qbuPrivate
{
public:
	QString m_strExpression;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression() : m_pPrivate{ std::make_unique<qbuPrivate>()}
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression(const qbuDBExpression & other) : m_pPrivate{ std::make_unique<qbuPrivate>() }
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression(const qbuDBColDef & colDef0) : m_pPrivate{ std::make_unique<qbuPrivate>() }
{
	m_pPrivate->m_strExpression = colDef0.getFullString();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::~qbuDBExpression()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBExpression::toString(bool *bOK /*= nullptr*/) const
{
	return m_pPrivate->m_strExpression;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBExpression::isValid() const
{
	return !isEmpty();
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBExpression::isEmpty() const
{
	return m_pPrivate->m_strExpression.isEmpty();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBExpression::copy(const qbuDBExpression & other)
{
	m_pPrivate->m_strExpression = other.m_pPrivate->m_strExpression;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression& qbuDBExpression::operator=(const qbuDBExpression & other)
{
	if (&other != this) {
		copy(other);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::date(QString strCol, QString strTableAlias /*= QString()*/)
{
	return unary_function("date", strCol, strTableAlias);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::datetime(QString strCol, QString strTableAlias /*= QString()*/)
{
	return unary_function("datetime", strCol, strTableAlias);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::unary_function(QString strFunction, QString strCol, QString strTableAlias /*= QString()*/)
{
	qbuDBExpression retVal;
	
	if ((!strFunction.isEmpty()) && (!strCol.isEmpty())){
		QString strColDef;
		if (strTableAlias.isEmpty()) {
			strColDef = QString("%1(%2)").arg(strFunction).arg(strCol);
		}
		else {
			strColDef = QString("%1(%2.%3)").arg(strFunction).arg(strTableAlias).arg(strCol);
		}

		retVal = qbuDBExpression(qbuDBColDef(strColDef, qbuDBColDef::OP_IS_EXPRESSION));

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::unary_function(QString strFunction, const qbuDBColDef & colDef)
{
	qbuDBExpression retVal;

	if (!strFunction.isEmpty()){
		QString strColDef = QString("%1(%2)").arg(strFunction).arg(colDef.getFullString());
		
		retVal = qbuDBExpression(qbuDBColDef(strColDef, qbuDBColDef::OP_IS_EXPRESSION));

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
