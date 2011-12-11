#ifndef __SMCREATEVIEWQUERY_H__
#define __SMCREATEVIEWQUERY_H__

#include "qbuQuery.h"

class qbuDatabase;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This class helps the process of creating a database View.
 *
 *	\ingroup qbuDatabase
 *
 */

class smCreateViewQuery : public qbuQuery
{
public:
	typedef qbuQuery Superclass;
public:
	smCreateViewQuery(QSqlDatabase db);
	virtual ~smCreateViewQuery();
public:
	bool	create(QString strViewName, QString strViewQuery, bool bTempView = false);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMCREATEVIEWQUERY_H__

