#ifndef __SMSELECTQUERY_H__
#define __SMSELECTQUERY_H__

#include "qbuQuery.h"
#include "qbuDBColumnDef.h"

class qbuPropertyMap;
class qbuDatabase;
class qbuDBColumnDefList;

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
	qbuSelectQuery(QSqlDatabase db);
	virtual ~qbuSelectQuery();
public:
	enum	SelectOption { QBU_SELECT_DEFAULT, QBU_SELECT_DISTINCT, QBU_SELECT_ALL };
public:
	virtual	bool	generateSQL(QString & strSQL);
	virtual bool	generateQuery();
public:
	bool	setSelectOption(SelectOption option);
	bool	addSelectField(QString strField,QString strAlias=QString(),QString strTableAlias=QString());
	bool	addSelectField(const qbuDBColDef & colDef);
	bool	addSelectFields(const QStringList & lstFields,QString strTableAlias=QString());
	bool	addFromField(QString strField,QString strAlias=QString());
	bool	addFromField(qbuSelectQuery & nestedQuery,QString strAlias);
	bool	setWhereClause(QString strWhere);
	bool	appendWhereExpression(QString strExpression);
	bool	appendWhereExpressions(QStringList & lstWhereFields, qbuPropertyMap* pProps);
	bool	addOrderByField(QString strField,QString strTableAlias=QString());
	bool	addGroupByField(QString strField,QString strTableAlias=QString());

	bool	addOrderByField(const qbuDBColDef & colDef);
	bool	addGroupByField(const qbuDBColDef & colDef);

	bool	addOrderByFields(const QStringList & lstFields, QString strTableAlias=QString() );
	bool	addGroupByFields(const QStringList & lstFields, QString strTableAlias=QString() );

	bool	appendHavingExpression(QString strExpression);
	
	bool	getRecord(qbuPropertyMap* pPropMap);

	qbuDBColumnDefList*	getSelectFields( );
public:
	static bool genExpr(QString & strExpr,qbuPropertyMap* pProps, QString strField, QString strTableAlias="",QString strOperator=QString("="));
	static QString genExpr(const qbuDBColDef & first, const qbuDBColDef & second,QString strOperator=QString("="));
	static QString genExpr(const qbuDBColDef & first, QString strSecond,QString strOperator=QString("="));
	static QString genExpr(QString strFirst, QString strSecond,QString strOperator=QString("="));
	static QString genExprTableAlias(QString strField, QString strTA1, QString strTA2, QString strOperator=QString("="));
public:
	static bool	g_bDumpQueries;
private:
	class	qbuPrivate;
	qbuPrivate*		m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMSELECTQUERY_H__

