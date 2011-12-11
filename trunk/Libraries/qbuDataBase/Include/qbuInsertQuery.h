#ifndef __SMINSERTQUERY_H__
#define __SMINSERTQUERY_H__

#include "qbuQuery.h"
#include "smMacros.h"
#include "qbuDBConstants.h"

class qbuDatabase;
class qbuPropertyMap;
class qbuTable;
class smSelectQuery;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This class helps the process of creating a database View.
 *
 *	\ingroup qbuDatabase
 *
 */

class qbuInsertQuery : public qbuQuery
{
	SM_DECLARE_SUPERCLASS(qbuQuery);
public:
	qbuInsertQuery(QSqlDatabase db);
	virtual ~qbuInsertQuery();

public:
	bool	create(qbuPropertyMap* pData,qbuTable* pTable,
		smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING );

	bool	create(smSelectQuery* pQuery,qbuTable* pTable,
		smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING );

	bool	generateQueryString(QString & strInsertQuery, smSelectQuery* pQuery,
		qbuTable* pTable, smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING );

	bool	generateQueryString(QString & strInsertQuery, 
		qbuPropertyMap* pData, qbuTable* pTable,
		smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING);
protected:
	QString handleInsertMode( smdb::InsertMode im );

private:
	/**
	 *	\note
	 *	The following member is very dangerous because it could result in
	 *  the wrong rows being matched up in the insert.
	 */
	bool	generateQueryString(QString & strInsertQuery, QString strQuery,
		QString strTable, smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING );
};

/////////////////////////////////////////////////////////////////////////////////////////




#endif //__SMINSERTQUERY_H__