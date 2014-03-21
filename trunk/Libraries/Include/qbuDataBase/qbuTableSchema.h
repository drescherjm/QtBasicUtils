#ifndef __SMTABLESCHEMA_H__
#define __SMTABLESCHEMA_H__

#include <QObject>
#include "qbuTableColumnDef.h"

class qbuTable;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class helps verify if the C++ table definition matches the database schema.
 *
 *	\ingroup qbuDatabase
 */

class qbuTableSchema : public QObject
{
public:
	qbuTableSchema(qbuTable* pTable);
public:
	virtual	bool	analyzeTable();
	virtual bool	verifyTable(qbuInfo* pInfo);
protected:
	qbuTableColumnDefList	m_lstColumns;
	qbuTable*				m_pTable;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMTABLESCHEMA_H__