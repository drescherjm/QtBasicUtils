#pragma once

#ifndef QBUQUERY_H
#define QBUQUERY_H

#include "qbuDataBase/qbuDataBaseLibraryDefines.h"
#include "qbuDataBase/qbuSimpleQuery.h"
#include "qbuDataBase/qbuDBColumnDef.h"
#include "qbuDataBase/qbuDBExpression.h"

class qbuPropertyMap;

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\ingroup qbuDatabase
*/

class qbuDataBase_EXPORT qbuQuery : public qbuSimpleQuery
{
public:
	typedef qbuSimpleQuery Superclass;
public:
	qbuQuery(std::shared_ptr<QSqlDatabase> pDB);

	enum WhereExprCode {
		WE_IGNORE_MISSING_FIELDS = 0,
		WE_FAIL_ON_MISSING_FIELDS,
		WE_IS_NULL_ON_MISSING_FIELDS,
	};
public:
	virtual 	bool	appendWhereExpression(QString strExpression);
	virtual		bool	appendWhereExpression(const qbuDBExpression & expr);
	virtual		bool	appendWhereExpressions(const QStringList & lstWhereFields, qbuPropertyMap* pProps, WhereExprCode code = WE_FAIL_ON_MISSING_FIELDS, 
		QString strTableAlias=QString());
public:
	static bool genExpr(QString & strExpr, qbuPropertyMap* pProps, QString strField, QString strTableAlias = "", QString strOperator = QString("="));
	static QString genExpr(const qbuDBColDef & first, const qbuDBColDef & second, QString strOperator = QString("="));
	static QString genExpr(const qbuDBColDef & first, QString strSecond, QString strOperator = QString("="));
	static QString genExpr(QString strFirst, QString strSecond, QString strOperator = QString("="));
	static QString genExprTableAlias(QString strField, QString strTA1, QString strTA2, QString strOperator = QString("="));
};
/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUQUERY_H
