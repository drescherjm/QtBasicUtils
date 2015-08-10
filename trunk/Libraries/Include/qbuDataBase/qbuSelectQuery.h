#pragma once

#ifndef QBUSELECTQUERY_H
#define QBUSELECTQUERY_H

#include "qbuQuery.h"
#include "qbuDBColumnDef.h"

class qbuPropertyMap;
class qbuDatabase;
class qbuDBColumnDefList;
class qbuDBJoin;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class helps in generating select queries.
 *
 *	\ingroup qbuDatabase
 *
 */

class qbuSelectQuery : public qbuQuery
{
public:
	typedef qbuQuery Superclass;
public:
	qbuSelectQuery(std::shared_ptr<QSqlDatabase> pDB);
	virtual ~qbuSelectQuery();
public:
	enum	SelectOption { QBU_SELECT_DEFAULT, QBU_SELECT_DISTINCT, QBU_SELECT_ALL };
public:
	virtual	bool	generateSQL(QString & strSQL);
	virtual bool	generateQuery();
public:
	bool	setSelectOption(SelectOption option);
	bool	addSelectField(QString strField, QString strAlias = QString(), QString strTableAlias = QString());
	bool	addSelectField(qbuDBExpression & expression, QString strAlias = QString());
	bool	addSelectField(const qbuDBColDef & colDef);
	bool	addSelectFields(const QStringList & lstFields, QString strTableAlias = QString());
	bool	addFromField(QString strField, QString strAlias = QString());
	bool	addFromField(qbuSelectQuery & nestedQuery, QString strAlias);
	bool	addJoin(const qbuDBJoin & DBJoin);
	bool	setWhereClause(QString strWhere);
	bool	appendWhereExpression(QString strExpression);
	bool	appendWhereExpression(const qbuDBExpression & expr);

	bool	addOrderByField(QString strField, QString strTableAlias = QString(), QString strASC = QString());
	bool	addGroupByField(QString strField, QString strTableAlias = QString());

	bool	addOrderByField(const qbuDBColDef & colDef);

	bool	addGroupByField(const qbuDBColDef & colDef);

	bool	addOrderByFields(const QStringList & lstFields, QString strTableAlias = QString(), QString strASC = QString());
	bool	addGroupByFields(const QStringList & lstFields, QString strTableAlias = QString());

	bool	appendHavingExpression(QString strExpression);

	bool	getRecord(qbuPropertyMap* pPropMap);

	qbuDBColumnDefList*	getSelectFields();

public:
	static bool	g_bDumpQueries;
private:
	class	smPrivate;
	std::unique_ptr<smPrivate>		m_pPrivate;
};
/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUSELECTQUERY_H
