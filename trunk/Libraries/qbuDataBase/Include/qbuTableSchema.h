#ifndef __SMTABLESCHEMA_H__
#define __SMTABLESCHEMA_H__

#include <QObject>
#include "smTableColumnDef.h"

class smTable;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class helps verify if the C++ table definition matches the database schema.
 *
 *	\ingroup smDatabase
 */

class smTableSchema : public QObject
{
public:
	smTableSchema(smTable* pTable);
public:
	virtual	bool	analyzeTable();
	virtual bool	verifyTable(smInfo* pInfo);
protected:
	smTableColumnDefList	m_lstColumns;
	smTable*				m_pTable;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMTABLESCHEMA_H__