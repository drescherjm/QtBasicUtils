#include "qbuDataBase/qbuCreateTableQuery.h"
#include <QStringList>
#include "qbuBase/Property.h"
#include "qbuPropertyMap.h"
#include <QList>
#include "qbuDatabaseFunctions.h"

/////////////////////////////////////////////////////////////////////////////////////////

struct sqlColumn
{
public:
	sqlColumn();
public:
	QString m_strColumnName;
	QString m_strDataType;
	QString m_strConstraints;
	bool	m_bPrimaryKey;
public:
	QString getColDef() const;
};

typedef QList<sqlColumn> sqlColumnList;

/////////////////////////////////////////////////////////////////////////////////////////

sqlColumn::sqlColumn() : m_bPrimaryKey(false)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

QString sqlColumn::getColDef() const
{
	QString retVal;
	retVal = m_strColumnName;
	if (!m_strDataType.isEmpty()) {
		retVal.append(" ");
		retVal.append(m_strDataType);
	}
	if (!m_strConstraints.isEmpty()) {
		retVal.append(" ");
		retVal.append(m_strConstraints);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

class qbuCreateTableQuery::qbuPrivate
{
public:
	qbuPrivate();
public:
	bool addColumn( QString strCoumnName,QString strDataType,QString strConstraint, bool bPrimaryKey );
	bool insertPrimaryKeys(QString & strQuery);
public:
	sqlColumnList		m_lstColumns;
	bool				m_bHasPrimaryKeys;
};

/////////////////////////////////////////////////////////////////////////////////////////

qbuCreateTableQuery::qbuPrivate::qbuPrivate() : m_bHasPrimaryKeys(false)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuCreateTableQuery::qbuPrivate::addColumn( QString strCoumnName,QString strDataType,
											   QString strConstraint, bool bPrimaryKey )
{
	bool retVal = (!strCoumnName.isEmpty());
	if (retVal) {
		sqlColumn column;
		column.m_strColumnName = doubleQuoteIfNecissary(strCoumnName);
		column.m_strConstraints = strConstraint;
		column.m_strDataType = strDataType;
		column.m_bPrimaryKey = bPrimaryKey;

		m_lstColumns.push_back(column);
		if (bPrimaryKey) {
			m_bHasPrimaryKeys = true;
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuCreateTableQuery::qbuPrivate::insertPrimaryKeys( QString & strQuery )
{
	bool retVal = !m_bHasPrimaryKeys;
	if (!retVal) {
		QString strTemp;
		sqlColumnList::iterator it = m_lstColumns.begin();
		for(;it != m_lstColumns.end();++it) {
			if (it->m_bPrimaryKey) {
				if (retVal) {
					strTemp.push_back(QString(", %1").arg(it->m_strColumnName));	
				}
				else {
					retVal = true;
					strTemp.push_back(QString(",PRIMARY KEY (%1").arg(it->m_strColumnName));
				}
			}
			
		}
		if (retVal) {
			strTemp.append(") ");
			strQuery.append(strTemp);
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuCreateTableQuery::qbuCreateTableQuery(QSqlDatabase db) : Superclass(db)
{
	m_pPrivate = new qbuPrivate();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuCreateTableQuery::~qbuCreateTableQuery()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuCreateTableQuery::addColumn( QString strCoumnName,QString strDataType,QString strConstraint/*=QString()*/ )
{
	bool retVal = (m_pPrivate != NULL);
	if (retVal) {
		retVal = m_pPrivate->addColumn(strCoumnName,strDataType,strConstraint,false);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuCreateTableQuery::addPKColumn( QString strCoumnName,QString strDataType,QString strConstraint/*=QString()*/ )
{
	bool retVal = (m_pPrivate != NULL);
	if (retVal) {
		retVal = m_pPrivate->addColumn(strCoumnName,strDataType,strConstraint,true);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuCreateTableQuery::generateColumnsQueryString()
{
	QString retVal;
	if (m_pPrivate != NULL) {
		sqlColumnList::iterator it = m_pPrivate->m_lstColumns.begin();
		retVal.push_back(it->getColDef());
		for(++it;it != m_pPrivate->m_lstColumns.end();++it) {
			retVal.push_back(QString(", %1").arg(it->getColDef()));	
		}
	}
	if (!retVal.isEmpty()) {
		m_pPrivate->insertPrimaryKeys(retVal);
		retVal.prepend("(");
		retVal.append(")");
	}
	return retVal;
}

