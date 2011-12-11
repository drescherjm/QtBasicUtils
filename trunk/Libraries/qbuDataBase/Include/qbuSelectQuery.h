#ifndef __SMSELECTQUERY_H__
#define __SMSELECTQUERY_H__

#include "smQuery.h"
#include "smDBColumnDef.h"

class smPropertyMap;
class smDatabase;
class smDBColumnDefList;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class helps in generating select queries.
 *
 *	\ingroup smDatabase
 *
 */

class smSelectQuery : public smQuery
{
public:
	typedef smQuery Superclass;
public:
	smSelectQuery(QSqlDatabase db);
	virtual ~smSelectQuery();
public:
	enum	SelectOption { SM_SELECT_DEFAULT, SM_SELECT_DISTINCT, SM_SELECT_ALL };
public:
	virtual	bool	generateSQL(QString & strSQL);
	virtual bool	generateQuery();
public:
	bool	setSelectOption(SelectOption option);
	bool	addSelectField(QString strField,QString strAlias=QString(),QString strTableAlias=QString());
	bool	addSelectField(const smDBColDef & colDef);
	bool	addSelectFields(const QStringList & lstFields,QString strTableAlias=QString());
	bool	addFromField(QString strField,QString strAlias=QString());
	bool	addFromField(smSelectQuery & nestedQuery,QString strAlias);
	bool	setWhereClause(QString strWhere);
	bool	appendWhereExpression(QString strExpression);
	bool	appendWhereExpressions(QStringList & lstWhereFields, smPropertyMap* pProps);
	bool	addOrderByField(QString strField,QString strTableAlias=QString());
	bool	addGroupByField(QString strField,QString strTableAlias=QString());

	bool	addOrderByField(const smDBColDef & colDef);
	bool	addGroupByField(const smDBColDef & colDef);

	bool	addOrderByFields(const QStringList & lstFields, QString strTableAlias=QString() );
	bool	addGroupByFields(const QStringList & lstFields, QString strTableAlias=QString() );

	bool	appendHavingExpression(QString strExpression);
	
	bool	getRecord(smPropertyMap* pPropMap);

	smDBColumnDefList*	getSelectFields( );
public:
	static bool genExpr(QString & strExpr,smPropertyMap* pProps, QString strField, QString strTableAlias="",QString strOperator=QString("="));
	static QString genExpr(const smDBColDef & first, const smDBColDef & second,QString strOperator=QString("="));
	static QString genExpr(const smDBColDef & first, QString strSecond,QString strOperator=QString("="));
	static QString genExpr(QString strFirst, QString strSecond,QString strOperator=QString("="));
	static QString genExprTableAlias(QString strField, QString strTA1, QString strTA2, QString strOperator=QString("="));
public:
	static bool	g_bDumpQueries;
private:
	class	smPrivate;
	smPrivate*		m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMSELECTQUERY_H__

