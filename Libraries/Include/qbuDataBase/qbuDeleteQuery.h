#pragma once

#ifndef QBUDELETEQUERY_H
#define QBUDELETEQUERY_H

//#include "qbuDatabaseLibraryDefines.h"
#include "qbuQuery.h"
#include "qbuDBColumnDef.h"
#include "qbuDBCondition.h"

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

class /*qbuDatabase_EXPORT*/ qbuDeleteQuery : public qbuQuery
{
public:
	typedef qbuQuery Superclass;
public:
	qbuDeleteQuery(std::shared_ptr<qbuDatabase> pDB);
	virtual ~qbuDeleteQuery();
public:
	virtual	bool	generateSQL(QString & strSQL);
	virtual bool	generateQuery();

public:
	bool	addFromField(QString strField,QString strAlias=QString());
	bool	addFromField(qbuDeleteQuery & nestedQuery,QString strAlias);
	bool	setWhereClause(QString strWhere);
	bool	appendWhereExpression(QString strExpression);
	bool	appendWhereExpression(const qbuDBCondition & expr);

	bool	go();

public:
	static bool	g_bDumpQueries;
private:
	class	qbuPrivate;
	qbuPrivate*		m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDELETEQUERY_H
