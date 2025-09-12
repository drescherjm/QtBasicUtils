#pragma once

#ifndef QBUTABLE_H
#define QBUTABLE_H

class qbuDatabase;
class qbuPropertyMap;
class qbuInfo;

#include <QStringList>
#include <memory>
#include <utility>
#include "qbuInsertQuery.h"
#include <QSharedPointer>
#include "qbuBase/qbuObject.h"

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This is the base class for all database tables.
 *
 *	\ingroup qbuDatabase
 */

class qbuTable : public qbuObject
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
	virtual const QStringList&	getOptionalPrimaryKeyList() const;
	virtual bool				verifyRequiredFields(qbuInfo * pInfo, bool bWarn=true) const;
	virtual bool				verifyRequiredFields(qbuInfo * pInfo, const QStringList & lst, bool bWarn=true) const;

	virtual int		count(QStringList lstWhereFields = QStringList(), 
		qbuPropertyMap* pPropMap = nullptr,
		const qbuDBCondition & expr = qbuDBCondition(),
		const QStringList & lstSelectFields = QStringList());

	virtual int		countDistinct(QStringList lstWhereFields = QStringList(),
		qbuPropertyMap* pPropMap = nullptr,
		const qbuDBCondition & expr = qbuDBCondition(),
		const QStringList & lstSelectFields = QStringList());


	std::pair<bool, QStringList>	getCurrentTableColumnNames(const QStringList& filter = {});

	template< typename T>
	bool	exportData(T*, QList< QSharedPointer<T> > & lst, qbuDBCondition expr = qbuDBCondition());

	template< typename T>
	bool	exportData(T*, QList< std::shared_ptr<T> > & lst, qbuDBCondition expr = qbuDBCondition());

protected:
	virtual bool				renameTable(QString strNewName);
	virtual bool				createTable(int nSchema)=0;
	virtual bool				internalCreateTable(QString strTableName, QString strTableSQL);
	virtual	bool				addColumn(QString strCoumnName,QString strDataType,QString strConstraint=QString());
	virtual bool				insertInitialValues(int nSchema) = 0;
	virtual QString				getTableName() const =0;
	virtual	bool				isValidField(QString strName);
	virtual	void				databaseError(QString strErrorMessage);

public:
	/**
	 *	This generates a select query to insert values from a qbuPropertyMap derivative
	 *  into the database.
	 */
	bool insertData(qbuPropertyMap* pData,qbudb::InsertMode im = qbudb::IM_NO_EXTRA_HANDLING);

	QString getUniqueTempTableName(QString strBase, int nIndexStart = 0) const;
	
protected:
	std::shared_ptr<qbuDatabase>		m_pDB;
};

/////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
bool qbuTable::exportData(T* pInfo, QList< QSharedPointer<T> > & lst, qbuDBCondition expr)
{

	qbuStringList lstWhereFields = pInfo->getDBFieldNames();
	bool retVal = true;
	if (retVal) {
		qbuSelectQuery query(m_pDB);
		query.addSelectFields(lstWhereFields);
		query.addFromField(getTableName());
		query.appendWhereExpressions(lstWhereFields, pInfo, qbuQuery::WE_IGNORE_MISSING_FIELDS);
		if (expr.isValid()) {
			query.appendWhereExpression(expr);
		}
		if (retVal) {
			retVal = query.generateQuery();
			if (retVal) {
				retVal = query.exec();
				if (retVal) {
					while (query.next() && retVal) {
                        T record;

						retVal = query.getRecord(&record);
						if (retVal) {

							QSharedPointer<T> ptr(new T(record));

							lst.push_back(ptr);
						}
					}
				}
			}
		}

	}
	return retVal;

}

/////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
bool qbuTable::exportData(T* pInfo, QList< std::shared_ptr<T> > & lst, qbuDBCondition expr)
{

	qbuStringList lstWhereFields = pInfo->getDBFieldNames();
	bool retVal = true;
	if (retVal) {
		qbuSelectQuery query(m_pDB);
		query.addSelectFields(lstWhereFields);
		query.addFromField(getTableName());
		query.appendWhereExpressions(lstWhereFields, pInfo, qbuQuery::WE_IGNORE_MISSING_FIELDS);
		if (expr.isValid()) {
			query.appendWhereExpression(expr);
		}
		if (retVal) {
			retVal = query.generateQuery();
			if (retVal) {
				retVal = query.exec();
				if (retVal) {
					while (query.next() && retVal) {
                        T record;

						retVal = query.getRecord(&record);
						if (retVal) {

							std::shared_ptr<T> ptr(new T(record));

							lst.push_back(ptr);
						}
					}
				}
			}
		}

	}
	return retVal;

}


/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUTABLE_H
