#pragma once

#ifndef QBUCREATETABLEQUERYEX_H
#define QBUCREATETABLEQUERYEX_H

#include "qbuDataBase/qbuCreateTableQuery.h"

class qbuSelectQuery;

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDataBase_EXPORT qbuCreateTableQueryEx : public qbuCreateTableQuery
{
	QBU_DECLARE_SUPERCLASS(qbuCreateTableQuery);
public:
	qbuCreateTableQueryEx(std::shared_ptr<QSqlDatabase> pDB);
	virtual ~qbuCreateTableQueryEx();
public:
	bool	createFromSelect(qbuSelectQuery & query);
	bool	generateCreateAndInsertQueriesFromSelect(qbuSelectQuery & query,
		QString strNewTableName,
		QString & strCreateTable,
		QString & strInsertData);

protected:
	virtual QString getExpectedTypeFromColumnName(QString strName);

private:
	class qbuPrivate;
	std::unique_ptr<qbuPrivate>		m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUCREATETABLEQUERYEX_H
