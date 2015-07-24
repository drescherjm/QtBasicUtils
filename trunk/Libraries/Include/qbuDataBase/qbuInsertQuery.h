#pragma once

#ifndef QBUINSERTQUERY_H
#define QBUINSERTQUERY_H

#include "qbuQuery.h"
#include "qbuBase/qbuMacros.h"
#include "qbuDBConstants.h"

class qbuDatabase;
class qbuPropertyMap;
class qbuTable;
class qbuSelectQuery;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This class helps the process of creating a database View.
 *
 *	\ingroup qbuDatabase
 *
 */

class qbuInsertQuery : public qbuQuery
{
	QBU_DECLARE_SUPERCLASS(qbuQuery);
public:
	qbuInsertQuery(std::shared_ptr<QSqlDatabase> pDB);
	virtual ~qbuInsertQuery();

public:
	bool	create(qbuPropertyMap* pData, qbuTable* pTable,
		smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING);

	bool	create(qbuSelectQuery* pQuery, qbuTable* pTable,
		smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING);

	bool	generateQueryString(QString & strInsertQuery, qbuSelectQuery* pQuery,
		qbuTable* pTable, smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING);

	bool	generateQueryString(QString & strInsertQuery,
		qbuPropertyMap* pData, qbuTable* pTable,
		smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING);
protected:
	QString handleInsertMode(smdb::InsertMode im);

private:
	/**
	*	\note
	*	The following member is very dangerous because it could result in
	*  the wrong rows being matched up in the insert.
	*/
	bool	generateQueryString(QString & strInsertQuery, QString strQuery,
		QString strTable, smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUINSERTQUERY_H
