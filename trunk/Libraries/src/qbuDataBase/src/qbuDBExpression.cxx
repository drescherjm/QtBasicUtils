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

qbuDBExpression qbuDBExpression::function(QString strFunction, QStringList lstCols, QString strTableAlias /*= QString()*/)
{
	qbuDBExpression retVal;

	if ((!strFunction.isEmpty()) && (!lstCols.isEmpty())) {
		QString strColDef;
		if (!strTableAlias.isEmpty()) {
			lstCols.prepend(QString("%1.").arg(strTableAlias));
		}
		strColDef = QString("%1( %2 )").arg(strFunction).arg(lstCols.join(','));
		
		retVal = qbuDBExpression(qbuDBColDef(strColDef, qbuDBColDef::OP_IS_EXPRESSION));

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::fromExpressionString(QString strExpression)
{
	return qbuDBExpression(qbuDBColDef(strExpression, qbuDBColDef::OP_IS_EXPRESSION));
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

qbuDBExpression qbuDBExpression::CAST(QString strCol, QString strTableAlias /*= QString()*/, QString castAs /*= QString("INT")*/)
{
	qbuDBExpression retVal;

	if ( (!strCol.isEmpty()) && (!castAs.isEmpty())) {
		QString strColDef;
		if (strTableAlias.isEmpty()) {
			strColDef = QString("CAST(%1 AS %2)").arg(strCol).arg(castAs);
		}
		else {
			strColDef = QString("CAST(%1.%2 AS %3)").arg(strTableAlias).arg(strCol).arg(castAs);
		}

		retVal = qbuDBExpression(qbuDBColDef(strColDef, qbuDBColDef::OP_IS_EXPRESSION));

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
