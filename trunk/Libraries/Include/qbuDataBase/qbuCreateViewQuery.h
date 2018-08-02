#pragma once

#ifndef QBUCREATEVIEWQUERY_H
#define QBUCREATEVIEWQUERY_H

#include "qbuDataBase/qbuQuery.h"

class qbuDatabase;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This class helps the process of creating a database View.
 *
 *	\ingroup qbuDatabase
 *
 */

class qbuCreateViewQuery : public qbuQuery
{
public:
	typedef qbuQuery Superclass;
public:
	qbuCreateViewQuery(std::shared_ptr<qbuDatabase> pDB);
	virtual ~qbuCreateViewQuery();
public:
	bool	create(QString strViewName, QString strViewQuery, bool bTempView = false);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUCREATEVIEWQUERY_H

