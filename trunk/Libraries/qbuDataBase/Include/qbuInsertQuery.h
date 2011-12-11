#ifndef __SMINSERTQUERY_H__
#define __SMINSERTQUERY_H__

#include "smQuery.h"
#include "smMacros.h"
#include "smDBConstants.h"

class smDatabase;
class smPropertyMap;
class smTable;
class smSelectQuery;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This class helps the process of creating a database View.
 *
 *	\ingroup smDatabase
 *
 */

class smInsertQuery : public smQuery
{
	SM_DECLARE_SUPERCLASS(smQuery);
public:
	smInsertQuery(QSqlDatabase db);
	virtual ~smInsertQuery();

public:
	bool	create(smPropertyMap* pData,smTable* pTable,
		smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING );

	bool	create(smSelectQuery* pQuery,smTable* pTable,
		smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING );

	bool	generateQueryString(QString & strInsertQuery, smSelectQuery* pQuery,
		smTable* pTable, smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING );

	bool	generateQueryString(QString & strInsertQuery, 
		smPropertyMap* pData, smTable* pTable,
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