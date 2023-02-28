#include "qbuDatabasePCH.h"

#include "qbuDataBase/qbuDBExpression.h"
#include "qbuDataBase/qbuDBColumnDef.h"
#include <memory>
#include "qbuDataBase/qbuDatabaseFunctions.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDBExpression::qbuPrivate
{
public:
	QString m_strExpression;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression() : m_pPrivate{ std::make_unique<qbuPrivate>() }
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression(const qbuDBExpression& other) : m_pPrivate{ std::make_unique<qbuPrivate>() }
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::qbuDBExpression(const qbuDBColDef& colDef0) : m_pPrivate{ std::make_unique<qbuPrivate>() }
{
	m_pPrivate->m_strExpression = colDef0.getFullString();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression::~qbuDBExpression()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBExpression::toString(bool* bOK /*= nullptr*/) const
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

void qbuDBExpression::copy(const qbuDBExpression& other)
{
	m_pPrivate->m_strExpression = other.m_pPrivate->m_strExpression;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression& qbuDBExpression::operator=(const qbuDBExpression& other)
{
	if (&other != this) {
		copy(other);
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::date(QString strCol, QString strTableAlias /*= QString()*/,
	const QStringList& lstModifiers)
{
	if (strCol.trimmed().compare("now", Qt::CaseInsensitive) == 0) {
		strCol = singleQuoteIfNotQuoted(strCol);
	}
	return date_functions("date", strCol, strTableAlias, lstModifiers);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::datetime(QString strCol, QString strTableAlias, const QStringList& lstModifiers)
{
	if (strCol.trimmed().compare("now", Qt::CaseInsensitive) == 0) {
		strCol = singleQuoteIfNotQuoted(strCol);
	}
	return date_functions("datetime", strCol, strTableAlias,lstModifiers);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::date_functions(QString strFunction, QString strDateCol, 
	QString strTableAlias /*= {}*/, const QStringList& lstModifiers /*= {}*/, QString strFormat)
{
	return date_functions(strFunction, qbuDBExpression(qbuDBColDef(strDateCol).addTableAlias(strTableAlias)), lstModifiers, strFormat);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::date_functions(QString strFunction, const qbuDBExpression& expr, const QStringList& lstModifiers /*= {}*/, QString strFormat /*= {}*/)
{
	qbuDBExpression retVal;

	if ((!strFunction.isEmpty()) && (!expr.isEmpty())) {

		strFormat = strFormat.trimmed();

		// strFormat should only be used for strftime
		if (!strFormat.isEmpty()) {
			strFormat.prepend('\'');
			strFormat.append("\', ");
		}

		QString strColDef;

		if (lstModifiers.isEmpty()) {
			strColDef = QString("%1( %2 %3 )").arg(strFunction).arg(strFormat).arg(expr.toString());
		}
		else {
			QStringList lst;
			for (QString str : lstModifiers) {
				str = str.trimmed();
				if (!str.isEmpty()) {
					lst.append(singleQuoteIfNotQuoted(str));
				}
			}
			strColDef = QString("%1( %2 %3, %4 )").arg(strFunction).arg(strFormat).arg(expr.toString()).arg(lst.join(", "));
		}

		retVal = qbuDBExpression(qbuDBColDef(strColDef, qbuDBColDef::OP_IS_EXPRESSION));

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::strftime(QString strFormat, QString strDateCol, QString strTableAlias /*= {}*/, 
	const QStringList& lstModifiers /*= {}*/)
{
	return date_functions("strftime", strDateCol, strTableAlias, lstModifiers,strFormat);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::strftime(QString strFormat, const qbuDBExpression& expr, const QStringList& lstModifiers /*= {}*/)
{
	return date_functions("strftime", expr, lstModifiers, strFormat);
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

qbuDBExpression qbuDBExpression::COALESCE(QStringList lstCols, QString strTableAlias)
{
	qbuDBExpression retVal;

	// Apply the table alias to all fields
	if (!strTableAlias.isEmpty()) {
		for (auto& col : lstCols) {
			col = QString("[%1].[%2]").arg(strTableAlias).arg(col);
		}
	}

	QString strColDef{ QString("COALESCE( %1 )").arg(lstCols.join(", ")) };

	retVal = qbuDBExpression(qbuDBColDef(strColDef, qbuDBColDef::OP_IS_EXPRESSION));

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBExpression qbuDBExpression::COALESCE(QList<qbuDBColDef> lstCols)
{
	QStringList lst;
	for (auto& col : lstCols) {
		lst.append(col.getFullString());
	}

	return COALESCE(lst,"");
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
