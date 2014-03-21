#ifndef __SMQUERY_H__
#define __SMQUERY_H__

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QList>

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\ingroup qbuDatabase
 */

class qbuQuery : public QSqlQuery
{
public:
	typedef QSqlQuery Superclass;
public:
	qbuQuery(QSqlDatabase db = QSqlDatabase());
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMQUERY_H__

