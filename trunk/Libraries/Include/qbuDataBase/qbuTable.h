#pragma once

#ifndef QBUTABLE_H
#define QBUTABLE_H

class qbuDatabase;
class qbuPropertyMap;
class qbuInfo;

#include <QObject>
#include <QStringList>
#include <memory>
#include "qbuInsertQuery.h"

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This is the base class for all database tables.
 *
 *	\ingroup qbuDatabase
 */

class qbuTable : public QObject
{
	friend class qbuTableSchema;
	friend class qbuInsertQuery;
public:
	qbuTable(std::shared_ptr<qbuDatabase> pDataBase);
	virtual ~qbuTable();

public:
	virtual bool	upgradeTable(int nOldSchema, int nNewSchema);
	virtual qbuInfo* createInfoClass() const =0;
	virtual bool	verifySchema();
	virtual bool	fixKnownProblems();
	virtual const QStringList&	getRequiredFieldList() const;
	virtual bool				verifyRequiredFields(qbuInfo * pInfo) const;
	virtual bool				verifyRequiredFields(qbuInfo * pInfo, const QStringList & lst) const;

	virtual int		count(QStringList lstFields = QStringList(), qbuPropertyMap* pPropMap = NULL);

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
	 *	This generates a select query to insert values from a qbuPropertyMap derivative
	 *  into the database.
	 */
	bool insertData(qbuPropertyMap* pData,smdb::InsertMode im = smdb::IM_NO_EXTRA_HANDLING);
	
protected:
	std::shared_ptr<qbuDatabase>		m_pDB;

private:
	class		qbuPrivate;
	qbuPrivate*	m_pPrivate;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUTABLE_H
