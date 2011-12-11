#ifndef __SMTABLE_H__
#define __SMTABLE_H__

class smDatabase;
class smPropertyMap;
class smInfo;

#include <QObject>
#include <QStringList>
#include "smInsertQuery.h"

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This is the base class for all database tables.
 *
 *	\ingroup smDatabase
 */

class smTable : public QObject
{
	friend class smTableSchema;
	friend class smInsertQuery;
public:
	smTable(smDatabase* pDataBase);
	virtual ~smTable();

public:
	virtual bool	upgradeTable(int nOldSchema, int nNewSchema);
	virtual smInfo* createInfoClass() const =0;
	virtual bool	verifySchema();
	virtual bool	fixKnownProblems();
	virtual const QStringList&	getRequiredFieldList() const;
	virtual bool				verifyRequiredFields(smInfo * pInfo) const;
	virtual bool				verifyRequiredFields(smInfo * pInfo, const QStringList & lst) const;

	virtual int		count(QStringList lstFields = QStringList(), smPropertyMap* pPropMap = NULL);

protected:
	virtual bool				renameTable(QString strNewName);
	virtual bool				createTable(int nSchema)=0;
	virtual bool				internalCreateTable(QString strTableName, QString strTableSQL);
	virtual	bool				addColumn(QString strCoumnName,QString strDataType,QString strConstraint=QString());
	virtual bool				insertInitialValues()=0;
	virtual QString				getTableName() const =0;
	virtual	bool				isValidField(QString strName);
public:
	/**
	 *	This generates a select query to insert values from a smPropertyMap derivative
	 *  into the database.
	 */
	bool insertData(smPropertyMap* pData,smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING);
	
protected:
	smDatabase*		m_pDB;
private:
	class		smPrivate;
	smPrivate*	m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMTABLE_H__
