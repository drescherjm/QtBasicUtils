#ifndef __SMQUERY_H__
#define __SMQUERY_H__

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QList>

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\ingroup smDatabase
 */

class smQuery : public QSqlQuery
{
public:
	typedef QSqlQuery Superclass;
public:
	smQuery(QSqlDatabase db = QSqlDatabase());
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMQUERY_H__

