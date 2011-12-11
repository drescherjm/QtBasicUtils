#ifndef __SMCREATEVIEWQUERY_H__
#define __SMCREATEVIEWQUERY_H__

#include "smQuery.h"

class smDatabase;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This class helps the process of creating a database View.
 *
 *	\ingroup smDatabase
 *
 */

class smCreateViewQuery : public smQuery
{
public:
	typedef smQuery Superclass;
public:
	smCreateViewQuery(QSqlDatabase db);
	virtual ~smCreateViewQuery();
public:
	bool	create(QString strViewName, QString strViewQuery, bool bTempView = false);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMCREATEVIEWQUERY_H__

