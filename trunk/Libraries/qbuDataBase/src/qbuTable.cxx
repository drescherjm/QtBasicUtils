#include "smDBBasePCH.h"
#include "smTable.h"
#include "smDatabase.h"
#include "smPropertyMap.h"
#include <QStringList>
#include <QSqlQuery>
#include "smException.h"
#include <iostream>
#include "smTableSchema.h"
#include "smStringList.h"
#include "..\smDatabase\smDatabasePCH.h"
#include "smLog.h"
#include "smSelectQuery.h"
#include "Property.h"

/////////////////////////////////////////////////////////////////////////////////////////

class smTable::smPrivate
{
public:

};

/////////////////////////////////////////////////////////////////////////////////////////

smTable::smTable( smDatabase* pDataBase ) : m_pDB(pDataBase)
{
	m_pPrivate = new smPrivate();	
}

/////////////////////////////////////////////////////////////////////////////////////////

smTable::~smTable()
{
	delete m_pPrivate;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief
*	This is the base upgradeTable. 
*	\details
*	This function checks if the table needs to be created. If so it does and calls
*  smTable::insertInitialValues() to insert these initial values. 
*/

bool smTable::upgradeTable( int nOldSchema, int nNewSchema )
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

#ifdef SM_HAVE_EXCEPTIONS
				throw smException(__FILE__,__LINE__,qPrintable(strError),"smTable::upgradeTable");
#endif //def SM_HAVE_EXCEPTIONS

			}
		}
	}
	if (retVal) {
		QLOG_INFO() << QString("The table %1 was upgraded to schema %2").arg(getTableName()).arg(nNewSchema);
	}
	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

bool smTable::insertData( smPropertyMap* pData,smdb::InsertMode im /*= IM_NO_EXTRA_HANDLING*/ )
{
	bool retVal = (pData != NULL);

	if (retVal) {
		smInsertQuery query(*m_pDB);
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

bool smTable::isValidField( QString strName )
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief
*	This member creates the table in the database using a CREATE TABLE SQL command.
*/

bool smTable::internalCreateTable( QString strTableName, QString strTableSQL )
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

#ifdef SM_HAVE_EXCEPTIONS
			throw smException(__FILE__,__LINE__,qPrintable(strError),"smTable::internalCreateTable");
#endif //def SM_HAVE_EXCEPTIONS

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief The purpose of the member function is to add a column to an existing table.
*/

bool smTable::addColumn( QString strCoumnName,QString strDataType,QString strConstraint/*=QString()*/ )
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

#ifdef SM_HAVE_EXCEPTIONS
			throw smException(__FILE__,__LINE__,qPrintable(strError),"smTable::addColumn");
#endif //def SM_HAVE_EXCEPTIONS

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smTable::renameTable( QString strNewName )
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

#ifdef SM_HAVE_EXCEPTIONS
			throw smException(__FILE__,__LINE__,qPrintable(strError),"smTable::renameTable");
#endif //def SM_HAVE_EXCEPTIONS

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smTable::verifySchema()
{
	smTableSchema schema(this);
	bool retVal = schema.analyzeTable();
	if (retVal) {

		std::auto_ptr<smInfo> ptr(createInfoClass());
		retVal = (ptr.get() != NULL);
		if (retVal) {
			retVal = schema.verifyTable(ptr.get());
		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

const QStringList& smTable::getRequiredFieldList() const
{
	static QStringList lst;
	return lst;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smTable::verifyRequiredFields( smInfo * pInfo ) const
{
	return verifyRequiredFields(pInfo,getRequiredFieldList());
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smTable::verifyRequiredFields( smInfo * pInfo, const QStringList & lstFields ) const
{
	bool retVal = (pInfo != NULL);
	if (retVal) {
		smStringList lstMissingRequired;

		const QStringList& lst = lstFields;
		foreach(QString str, lst) {
			if (!pInfo->hasField(str)) {
				lstMissingRequired.push_back(str);
			}
		}

		retVal = lstMissingRequired.isEmpty();
		if (!retVal) {
			QLOG_WARN() << "A query on table " << qPrintable(getTableName())
				<< " will fail because the following fields are not defined in the smInfo class: " << qPrintable(lstMissingRequired.toCSVString());

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

bool smTable::fixKnownProblems()
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

int smTable::count( QStringList lstFields /*= QStringList()*/, smPropertyMap* pPropMap /*= NULL*/ )
{
	int retVal = -1;
	smSelectQuery query(*m_pDB);

	// Setup a typical Count(*) query
	smDBColDef countval = smDBColDef("COUNT(*)",false).addAlias("Count");

	query.addSelectField(countval);
	query.addFromField(getTableName());

	// Add where expressions if necissary..
	if (pPropMap != NULL) {
		query.appendWhereExpressions(lstFields,pPropMap);
	}

	// Now get the value of the count.
	if (query.generateQuery() && query.exec() && query.next()) {
		smPropertyMap ret;
		if (query.getRecord(&ret)) {
			ret.getField<int>("Count",retVal);
		}
	}
	
	return retVal;
}
