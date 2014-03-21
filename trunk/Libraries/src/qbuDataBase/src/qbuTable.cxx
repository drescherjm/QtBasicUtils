#include "qbuDataBase/qbuTable.h"
#include "qbuDataBase/qbuDatabase.h"
#include "qbuDataBase/qbuPropertyMap.h"
#include <QStringList>
#include <QSqlQuery>
#include "qbuDataBase/qbuException.h"
#include <iostream>
#include "qbuDataBase/qbuTableSchema.h"
#include "qbuDataBase/qbuStringList.h"
#include "..\qbuDatabase\qbuDatabasePCH.h"
#include "smLog.h"
#include "qbuDataBase/qbuSelectQuery.h"
#include "qbuBase/Property.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuTable::qbuPrivate
{
public:

};

/////////////////////////////////////////////////////////////////////////////////////////

qbuTable::qbuTable( qbuDatabase* pDataBase ) : m_pDB(pDataBase)
{
	m_pPrivate = new qbuPrivate();	
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuTable::~qbuTable()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief
*	This is the base upgradeTable. 
*	\details
*	This function checks if the table needs to be created. If so it does and calls
*  qbuTable::insertInitialValues() to insert these initial values. 
*/

bool qbuTable::upgradeTable( int nOldSchema, int nNewSchema )
{
	bool retVal = m_pDB->tableExists(getTableName()) ;
	if (!retVal) {
		retVal = createTable( nNewSchema );
		if (retVal) {
			retVal = insertInitialValues();
			if (!retVal) {

				QString strError = QString("ERROR: Could not initialize table %1")
					.arg(getTableName());

				QLOG_CRIT() << strError;

#ifdef QBU_HAVE_EXCEPTIONS
				throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuTable::upgradeTable");
#endif //def QBU_HAVE_EXCEPTIONS

			}
		}
	}
	if (retVal) {
		QLOG_INFO() << QString("The table %1 was upgraded to schema %2").arg(getTableName()).arg(nNewSchema);
	}
	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::insertData( qbuPropertyMap* pData,smdb::InsertMode im /*= IM_NO_EXTRA_HANDLING*/ )
{
	bool retVal = (pData != NULL);

	if (retVal) {
		qbuInsertQuery query(*m_pDB);
		retVal = query.create(pData,this,im);
		if (retVal) {
			retVal = query.exec();
			if (!retVal) {
				// 

				QString strError = QString("Failed to insert data into the table %1. Using the following query: ").arg(getTableName());
				QLOG_CRIT() << strError;

				QString str;
				if (!query.generateQueryString(str,pData,this,im)) {
					str = query.executedQuery(); 
				}
				
				QLOG_CRIT() << str;

				pData->Print( std::cerr );


			}
		}

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::isValidField( QString strName )
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief
*	This member creates the table in the database using a CREATE TABLE SQL command.
*/

bool qbuTable::internalCreateTable( QString strTableName, QString strTableSQL )
{
	bool retVal = ( m_pDB != NULL) && (m_pDB->isOpen());
	if (retVal) {
		QString	CREATE_TABLE =QString("CREATE TABLE %1 %2;").arg(strTableName).arg(strTableSQL);
		QSqlQuery	query(*m_pDB);

		retVal = query.exec(CREATE_TABLE);
		if(retVal)
		{
			QLOG_INFO() << "Table" << qPrintable(strTableName) << "created";
		}
		else
		{
			QString strError = QString("%1 %2 %3")
				.arg("Failed to create table")
				.arg(strTableName)
				.arg(query.lastError().text());


			QLOG_CRIT() << qPrintable(strError);

#ifdef QBU_HAVE_EXCEPTIONS
			throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuTable::internalCreateTable");
#endif //def QBU_HAVE_EXCEPTIONS

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief The purpose of the member function is to add a column to an existing table.
*/

bool qbuTable::addColumn( QString strCoumnName,QString strDataType,QString strConstraint/*=QString()*/ )
{
	bool retVal = ( m_pDB != NULL) && (m_pDB->isOpen());
	if (retVal) {
		QString strSQL;
		strSQL = QString("ALTER TABLE %1 ADD COLUMN %2 %3 %4")
			.arg(getTableName())
			.arg(strCoumnName)
			.arg(strDataType)
			.arg(strConstraint);

		QSqlQuery	query(*m_pDB);

		retVal = query.exec(strSQL);
		if(retVal)
		{
			QLOG_INFO() << "Column " << qPrintable(strCoumnName) << " added to table " << qPrintable(getTableName());
		}
		else
		{
			QString strError = QString("Failed to add column %1 to table %2. The database error message was %3.")
				.arg(strCoumnName)
				.arg(getTableName())
				.arg(query.lastError().text());
			
			QLOG_CRIT() << qPrintable(strError);

#ifdef QBU_HAVE_EXCEPTIONS
			throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuTable::addColumn");
#endif //def QBU_HAVE_EXCEPTIONS

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::renameTable( QString strNewName )
{
	bool retVal = ( m_pDB != NULL) && (m_pDB->isOpen());
	if (retVal) {
		QString strSQL;
		strSQL = QString("ALTER TABLE %1 RENAME TO %2")
			.arg(getTableName())
			.arg(strNewName);

		QSqlQuery	query(*m_pDB);

		retVal = query.exec(strSQL);
		if(retVal)
		{
			QLOG_INFO() << "Table " << qPrintable(getTableName()) << " renamed to " << qPrintable(strNewName);
		}
		else
		{
			QString strError = QString("Failed to rename table %1 to %2. The database error message was %3.")
				.arg(getTableName())
				.arg(strNewName)
				.arg(query.lastError().text());
			
			
			QLOG_CRIT() << qPrintable(strError);

#ifdef QBU_HAVE_EXCEPTIONS
			throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuTable::renameTable");
#endif //def QBU_HAVE_EXCEPTIONS

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::verifySchema()
{
	qbuTableSchema schema(this);
	bool retVal = schema.analyzeTable();
	if (retVal) {

		std::auto_ptr<qbuInfo> ptr(createInfoClass());
		retVal = (ptr.get() != NULL);
		if (retVal) {
			retVal = schema.verifyTable(ptr.get());
		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

const QStringList& qbuTable::getRequiredFieldList() const
{
	static QStringList lst;
	return lst;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::verifyRequiredFields( qbuInfo * pInfo ) const
{
	return verifyRequiredFields(pInfo,getRequiredFieldList());
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::verifyRequiredFields( qbuInfo * pInfo, const QStringList & lstFields ) const
{
	bool retVal = (pInfo != NULL);
	if (retVal) {
		qbuStringList lstMissingRequired;

		const QStringList& lst = lstFields;
		foreach(QString str, lst) {
			if (!pInfo->hasField(str)) {
				lstMissingRequired.push_back(str);
			}
		}

		retVal = lstMissingRequired.isEmpty();
		if (!retVal) {
			QLOG_WARN() << "A query on table " << qPrintable(getTableName())
				<< " will fail because the following fields are not defined in the qbuInfo class: " << qPrintable(lstMissingRequired.toCSVString());

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member fixes known bad data in the table.
 *
 *	\details
 *	The base class implementation does nothing override in the child to perform  fixes 
 *	for a table.
 *
 */

bool qbuTable::fixKnownProblems()
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

int qbuTable::count( QStringList lstFields /*= QStringList()*/, qbuPropertyMap* pPropMap /*= NULL*/ )
{
	int retVal = -1;
	qbuSelectQuery query(*m_pDB);

	// Setup a typical Count(*) query
	qbuDBColDef countval = qbuDBColDef("COUNT(*)",false).addAlias("Count");

	query.addSelectField(countval);
	query.addFromField(getTableName());

	// Add where expressions if necissary..
	if (pPropMap != NULL) {
		query.appendWhereExpressions(lstFields,pPropMap);
	}

	// Now get the value of the count.
	if (query.generateQuery() && query.exec() && query.next()) {
		qbuPropertyMap ret;
		if (query.getRecord(&ret)) {
			ret.getField<int>("Count",retVal);
		}
	}
	
	return retVal;
}
