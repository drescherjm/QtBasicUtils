#pragma once

#ifndef QBUCREATETABLEQUERY_H
#define QBUCREATETABLEQUERY_H

#include "qbuDataBase/qbuQuery.h"
#include <memory>

class qbuDatabase;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class helps in creating database queries.
 *
 *	\ingroup qbuDatabase
 *
*/

class qbuCreateTableQuery : public qbuQuery
{
public:
	typedef qbuQuery Superclass;
public:
	qbuCreateTableQuery(std::shared_ptr<QSqlDatabase> pDB);
	virtual ~qbuCreateTableQuery();
public:
	bool	addColumn(QString strCoumnName,QString strDataType,QString strConstraint=QString());
	bool	addPKColumn(QString strCoumnName,QString strDataType,QString strConstraint /*=QString("NOT NULL")*/);
	
	// Note this is only the column definitions.
	QString generateColumnsQueryString();
private:
	class	qbuPrivate;
	qbuPrivate*		m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUCREATETABLEQUERY_H
