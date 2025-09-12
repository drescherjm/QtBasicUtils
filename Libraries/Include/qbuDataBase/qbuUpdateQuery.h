#pragma once

#ifndef QBUUPDATEQUERY_H
#define QBUUPDATEQUERY_H

#include "qbuQuery.h"
#include "qbuDBColumnDef.h"

class qbuPropertyMap;
class qbuDatabase;
class qbuDBColumnDefList;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class helps in generating update queries.
 *
 *	\ingroup qbuDatabase
 *
 */

class qbuUpdateQuery : public qbuQuery
{
public:
	typedef qbuQuery Superclass;
public:
	qbuUpdateQuery(std::shared_ptr<qbuDatabase> pDB);
	virtual ~qbuUpdateQuery();

	enum UpdateExprCode {
		UE_IGNORE_MISSING_FIELDS = 0,
		UE_FAIL_ON_MISSING_FIELDS
	};

public:
	virtual	bool	generateSQL(QString & strSQL);
	virtual bool	generateQuery();

public:
	bool	addFromField(QString strField,QString strAlias=QString());
	bool	addFromField(qbuUpdateQuery & nestedQuery,QString strAlias);
	bool	addSetExpression(QString strExpression);
	bool	addSetExpressions(const QStringList & lstWhereFields, qbuPropertyMap* pProps, 
		UpdateExprCode code = UE_IGNORE_MISSING_FIELDS);
	bool	setWhereClause(QString strWhere);
	bool	appendWhereExpression(QString strExpression);
	using	Superclass::appendWhereExpression;
/*	bool	appendWhereExpressions(QStringList & lstWhereFields, qbuPropertyMap* pProps);*/
	bool	go();

public:
	static bool genSetExpr(QString & strExpr, qbuPropertyMap* pProps, QString strField, QString strTableAlias = "");

public:
	static bool	g_bDumpQueries;
private:
	class	qbuPrivate;
	qbuPrivate*		m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUUPDATEQUERY_H
