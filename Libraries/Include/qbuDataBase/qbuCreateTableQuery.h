#pragma once

#ifndef QBUCREATETABLEQUERY_H
#define QBUCREATETABLEQUERY_H

#include "qbuDataBase/qbuQuery.h"
#include <memory>

class qbuDatabase;
class qbuCTSQLColumn;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class helps in creating database queries.
 *
 *	\ingroup qbuDatabase
 *
*/

class qbuDataBase_EXPORT qbuCreateTableQuery : public qbuQuery
{
public:
	typedef qbuQuery Superclass; 
	typedef QList<qbuCTSQLColumn> sqlColumnList;

public:
	qbuCreateTableQuery(std::shared_ptr<qbuDatabase> pDB);
	virtual ~qbuCreateTableQuery();
public:
	virtual bool	addColumn(QString strCoumnName,QString strDataType,QString strConstraint=QString());
	virtual bool	addPKColumn(QString strCoumnName,QString strDataType,QString strConstraint /*=QString("NOT NULL")*/);
	
	// Note this is only the column definitions.
	virtual QString generateColumnsQueryString();

protected:
	bool	doesColumnExist(QString strColumnName);
	sqlColumnList* getColumnList();

private:
	class	qbuPrivate;
	qbuPrivate*		m_pPrivate;
};



/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUCREATETABLEQUERY_H
