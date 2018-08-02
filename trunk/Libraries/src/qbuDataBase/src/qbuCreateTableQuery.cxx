#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuCreateTableQuery.h"
#include "qbuDataBase/qbuCTSQLColumn.h"
#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuDataBase/qbuDatabaseFunctions.h"

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
		qbuCTSQLColumn column;
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

qbuCreateTableQuery::qbuCreateTableQuery(std::shared_ptr<qbuDatabase> pDB) : Superclass(pDB)
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

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuCreateTableQuery::doesColumnExist(QString strColumnName)
{
	bool retVal = false;

	foreach(auto sqlColumn, m_pPrivate->m_lstColumns) {
		retVal = (sqlColumn.m_strColumnName.compare(strColumnName.trimmed(), Qt::CaseInsensitive) == 0);

		if (retVal) {
			break;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuCreateTableQuery::sqlColumnList* qbuCreateTableQuery::getColumnList()
{
	return &m_pPrivate->m_lstColumns;
}

/////////////////////////////////////////////////////////////////////////////////////////
