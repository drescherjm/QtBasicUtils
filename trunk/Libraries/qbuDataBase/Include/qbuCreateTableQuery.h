#ifndef __SMCREATETABLEQUERY_H__
#define __SMCREATETABLEQUERY_H__

#include "smQuery.h"

class smDatabase;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class helps in creating database queries.
 *
 *	\ingroup smDatabase
 *
*/

class smCreateTableQuery : public smQuery
{
public:
	typedef smQuery Superclass;
public:
	smCreateTableQuery(QSqlDatabase db);
	virtual ~smCreateTableQuery();
public:
	bool	addColumn(QString strCoumnName,QString strDataType,QString strConstraint=QString());
	bool	addPKColumn(QString strCoumnName,QString strDataType,QString strConstraint /*=QString("NOT NULL")*/);
	
	// Note this is only the column definitions.
	QString generateColumnsQueryString();
private:
	class	smPrivate;
	smPrivate*		m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMCREATETABLEQUERY_H__

