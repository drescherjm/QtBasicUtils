#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDatabase.h"

#include <QSqlQuery>
#include <QVariant>
#include <QStringList>
#include <QDebug>
#include <QSqlError>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include "qbuDataBase/qbuDatabaseFunctions.h"
#include <iostream>
//#include "../qbuDBTables/include/qbuDBSettingsTableBase.h"

using namespace ::boost;
using namespace ::boost::multi_index;

/////////////////////////////////////////////////////////////////////////////////////////

struct attachedDB
{
public:
	attachedDB();
public:
	int			m_nCount;
	QString		m_strName;
	QString		m_strAlias;
};

/////////////////////////////////////////////////////////////////////////////////////////

attachedDB::attachedDB() : m_nCount(0)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

class qbuDatabase::qbuPrivate
{
public:
	~qbuPrivate();
public:
	struct DBName {};
	struct DBAlias {};

	typedef boost::multi_index_container<
		attachedDB,
		indexed_by< 
		ordered_unique< tag<DBName>,BOOST_MULTI_INDEX_MEMBER(attachedDB,QString, m_strName) >,
		ordered_unique< tag<DBAlias>,BOOST_MULTI_INDEX_MEMBER(attachedDB,QString, m_strAlias) >
		>
	> setAttachedDB;
public:
	bool	isDatabaseAttached( QString strDatabaseFileName, QString & strDBAlias );
	bool	incrementAttachedCount(QString strDatabaseFileName);
	bool	decrementAttachedCount(QString strDatabaseFileName);
	bool	detachDatabaseByAlias(qbuDatabase* pPublic,QString strAlias);
	bool	detachDatabaseByName(qbuDatabase* pPublic,QString strDBName);
	template<typename tag>
	bool	detachDatabase(qbuDatabase* pPublic,QString strKey);
public:
	setAttachedDB	m_setAttachedDBs;
};

/////////////////////////////////////////////////////////////////////////////////////////

template<typename tag>
bool qbuDatabase::qbuPrivate::detachDatabase( qbuDatabase* pPublic,QString strKey )
{
	bool retVal = (pPublic != NULL);
	if (retVal) {
		setAttachedDB::index<tag>::type::iterator it = m_setAttachedDBs.get<tag>().find(strKey);
		retVal = (it != m_setAttachedDBs.get<tag>().end());
		if (retVal) {
			retVal = (it->m_nCount > 0);
			if (retVal) {
				if (it->m_nCount > 1) {
					attachedDB db = *it;
					db.m_nCount--;
					m_setAttachedDBs.get<tag>().replace(it,db);
				}
				else
				{
					QString strQuery = QString("DETACH DATABASE \"%1\"").arg(it->m_strAlias);
					QSqlQuery query(*pPublic);
					retVal = query.exec(strQuery);
					m_setAttachedDBs.get<tag>().erase(it);
				}
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDatabase::qbuPrivate::~qbuPrivate()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::qbuPrivate::isDatabaseAttached( QString strDatabaseFileName, QString & strDBAlias )
{
	setAttachedDB::iterator it = m_setAttachedDBs.get<DBName>().find(strDatabaseFileName);
	bool retVal = (it != m_setAttachedDBs.end());
	if (retVal) {
		strDBAlias = it->m_strAlias;
	}
	return 	retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::qbuPrivate::incrementAttachedCount( QString strDatabaseFileName )
{
	setAttachedDB::iterator it = m_setAttachedDBs.get<DBName>().find(strDatabaseFileName);
	bool retVal = (it != m_setAttachedDBs.end());
	if (retVal) {
		attachedDB db = *it;
		db.m_nCount++;
		m_setAttachedDBs.replace(it,db);
	}
	return 	retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::qbuPrivate::decrementAttachedCount( QString strDatabaseFileName )
{
	setAttachedDB::iterator it = m_setAttachedDBs.get<DBName>().find(strDatabaseFileName);
	bool retVal = (it != m_setAttachedDBs.end());
	if (retVal) {
		attachedDB db = *it;
		db.m_nCount--;
		m_setAttachedDBs.replace(it,db);
	}
	return 	retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::qbuPrivate::detachDatabaseByAlias( qbuDatabase* pPublic,QString strAlias )
{
	bool retVal = (pPublic != NULL);
	if (retVal) {
		retVal = detachDatabase<DBAlias>(pPublic,strAlias);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::qbuPrivate::detachDatabaseByName( qbuDatabase* pPublic,QString strDBName )
{
	bool retVal = (pPublic != NULL);
	if (retVal) {
		retVal = detachDatabase<DBName>(pPublic,strDBName);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDatabase::qbuDatabase() : Superclass()
{
	m_pPrivate = new qbuPrivate();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDatabase::qbuDatabase( const qbuDatabase &other ) : Superclass(other)
{
	m_pPrivate = new qbuPrivate();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDatabase::qbuDatabase( const Superclass &other ) : Superclass(other)
{
	m_pPrivate = new qbuPrivate();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDatabase::~qbuDatabase()
{
	destroy();
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member function returns the schema version that has been set in the database.
 *
 *	\note
 *	I know that SQLITE has a built in schema but at this time I would like to be
 *	database independent on this. As a result of this, I create a table DBSettings table 
 *	in each database and in that settings table a row with Name SCHEMA_VERSION will 
 *	contain the schema version in the value column for that row.
 *	
 */

int qbuDatabase::getDBSchemaVersion()
{
	int retVal = -1;
	if (isOpen()) {
		/*
		QString strQuery = QString("SELECT Value FROM %1 WHERE Name = 'SCHEMA_VERSION'").arg(g_strDBSettingsTable);
		QSqlQuery query(strQuery,*this);
		if (query.next()) {
			retVal = query.value(0).toInt();
		}
		*/

		std::auto_ptr<qbuDBSettingsTableBase> pSettingsTable(getSettingsTable());
		if (pSettingsTable.get() != NULL) {
			retVal = pSettingsTable->getDBSchemaVersion();
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDatabase & qbuDatabase::operator=( const qbuDatabase &other )
{
	Superclass::operator=(other);

	if ( &other != this ) {
		destroy();
		copy(other);
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDatabase & qbuDatabase::operator=( const Superclass &other )
{
	Superclass::operator=(other);

	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member function performs a database upgrade.
 *
 *	\details
 *	The upgrade only happens if the current database schema is lower than the schema 
 *  version that this code provides..
 */

bool qbuDatabase::performUpgrade()
{
	bool retVal = isOpen();
	if (retVal) {
		int nSchema = getDBSchemaVersion();
		if (needsUpgrade(nSchema)) {
			int nOldSchema = getApplicationSchemaVersion();
			retVal = preUpgradeDB(nSchema,nOldSchema);
			if (retVal) {
				retVal = upgradeDB(nSchema,nOldSchema);
			}
		}
	}
	if (!retVal) {
		qDebug() << "Database Upgrade Failed at performUpgrade()";
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class returns the code database schema version.
 *
 *	\note
 *	Derived classes should override this function to return the schema version of the
 *	code for that database instead of the default schema version of 0.
 *
 */

int qbuDatabase::getApplicationSchemaVersion()
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member function determines if the database schema needs to be upgraded. 
 */

bool qbuDatabase::needsUpgrade( int nSchema/*=-2*/ )
{
	bool retVal = (nSchema < 0);
	if (retVal) {
		nSchema = getDBSchemaVersion();
	}

	retVal = (nSchema < getApplicationSchemaVersion());

	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This performs actions that need to be done before adding tables and views.
 *	\details
 *	At this moment this member only creates the DBSettings table. The reason for needing
 *	this now is views that depend on this table will fail to be added if it did not 
 *	exist.
 */

bool qbuDatabase::preUpgradeDB( int nOldSchema, int nNewSchema )
{
	bool retVal;
	retVal = tableExists(qbuDBSettingsTableBase::g_strTable);
	if (!retVal) {
		retVal = createSettingsTable();
	}
	if (retVal) {
		// Update the settings table.
		std::auto_ptr<qbuDBSettingsTableBase> pSettingsTable(getSettingsTable());
		retVal = (pSettingsTable.get() != NULL);
		if (retVal) {
			pSettingsTable->upgradeTable(nOldSchema,nNewSchema);
		}
	}
	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////


/**
 *	\brief 
 *	This member function upgrades the database to a new schema. 
 *
 *	\details
 *	This base member function takes care of upgrading the actual schema version that is
 *	stored in the database. 
 *
 *	\note
 *	All of the actual schema updates (adding columns to tables, adjusting data, ...)
 *	would have already been done in the upgradeDB() member functioin in the derived 
 *	database class.
 *
 */

bool qbuDatabase::upgradeDB( int nOldSchema, int nNewSchema )
{
	bool retVal = (nOldSchema == nNewSchema);
	if (!retVal) {
		retVal = setDBSchemaVersion(nNewSchema);
	}
	if (!retVal) {
		qDebug() << "Database Upgrade Failed";
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member creates a table called DBSettings.
 *	\sa qbuDatabase::getDBSchemaVersion
 */

bool qbuDatabase::createSettingsTable()
{
	bool retVal = isOpen();
	if (retVal) {

		std::auto_ptr<qbuDBSettingsTableBase> pSettingsTable(getSettingsTable());
		retVal = (pSettingsTable.get() != NULL);
		if (retVal) {
			pSettingsTable->createTable(0);
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::setDBSchemaVersion( int nSchema )
{
	bool retVal = isOpen();
	if (retVal) {
				
		std::auto_ptr<qbuDBSettingsTableBase> pSettingsTable(getSettingsTable());
		retVal = (pSettingsTable.get() != NULL);
		if (retVal) {
			pSettingsTable->setDBSchemaVersion(nSchema);
		}

	}
	else
	{
		qDebug() << "ERROR: The database is not open." ;

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDatabase::copy( const qbuDatabase & other )
{
	if (m_pPrivate == NULL) {
		m_pPrivate = new qbuPrivate();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDatabase::destroy()
{
	delete m_pPrivate;
	m_pPrivate = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::attachDatabase( QString strDatabaseFileName, QString strDBAlias )
{
	bool retVal = false;

	QString strAttachedAlias;
	if (isDatabaseAttached(strDatabaseFileName,strAttachedAlias)) {
		retVal = (strAttachedAlias.compare(strDBAlias,Qt::CaseInsensitive) == 0);
		if (retVal) {
			retVal = m_pPrivate->incrementAttachedCount(strDatabaseFileName);
		}
	}
	else
	{
		QString strQuery = QString("ATTACH DATABASE \"%1\" AS %2").arg(strDatabaseFileName).arg(doubleQuoteIfNecissary(strDBAlias));
		QSqlQuery query(*this);
		retVal = query.exec(strQuery);
		if (retVal && m_pPrivate) {
			attachedDB db;
			db.m_nCount = 1;
			db.m_strAlias = strDBAlias;
			db.m_strName = strDatabaseFileName;
			m_pPrivate->m_setAttachedDBs.insert(db);
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::attachDatabase( qbuDatabase* pDB, QString strDBAlias )
{
	bool retVal = (pDB != NULL);
	if (retVal) {
		QString strConnection = pDB->databaseName();
		retVal = !strConnection.isEmpty();
		if (retVal) {
			retVal = attachDatabase(strConnection,strDBAlias);
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDatabase::generateConnectionName( QString strDataBaseName )
{
	return QString("__%1").arg(strDataBaseName);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::hasConnection()
{
	QString strConnection = connectionName();
	return !strConnection.isEmpty();
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member function returns true if the table exists in this database.
 */

bool qbuDatabase::tableExists( QString strTableName, Qt::CaseSensitivity cs )
{
	QStringList lstTables = tables();
	return lstTables.contains(strTableName,cs);
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member function returns true if the view exists in this database.
 */


bool qbuDatabase::viewExists( QString strTableName, Qt::CaseSensitivity cs /*= Qt::CaseInsensitive*/ )
{
	QStringList lstViews = tables(QSql::Views);
	return lstViews.contains(strTableName,cs);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::verifyDBSchema()
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::isDatabaseAttached( QString strDatabaseFileName, QString & strDBAlias )
{
	return (m_pPrivate != NULL) ? m_pPrivate->isDatabaseAttached(strDatabaseFileName,strDBAlias) : false;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::detachDatabaseByAlias( QString strDBAlias )
{
	return (m_pPrivate != NULL) ? m_pPrivate->detachDatabaseByAlias(this,strDBAlias) : false;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::detachDatabaseByName( QString strDBName )
{
	return (m_pPrivate != NULL) ? m_pPrivate->detachDatabaseByName(this,strDBName) : false;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member verifies if we called verify on all tables that exist in the database.
 */

bool qbuDatabase::verifyCoverage( qbuStringList & lstSucceeded, qbuStringList & lstFailed )
{
	bool retVal = (!lstSucceeded.isEmpty() || !lstFailed.isEmpty());
	if (retVal) {
		
		qbuStringList lstTables = tables();
		qbuStringList lstExtra;
		qbuStringList lstTemp;

		// First match all tables where the verify succeeded.
		foreach(QString str,lstSucceeded) {
			if (lstTables.contains(str,Qt::CaseInsensitive)) {
				lstTables.removeAll(str,Qt::CaseInsensitive);
			}
			else
			{
				// Does this even make sense? I mean verifying a table that does not 
				// exist in the database would have failed anyways.
				lstExtra.append(str);
				retVal = false;
			}
		}

		// Next match all that the verify failed.
		foreach(QString str,lstFailed) {
			if (lstTables.contains(str,Qt::CaseInsensitive)) {
				lstTables.removeAll(str,Qt::CaseInsensitive);
			}
			else
			{
				lstExtra.append(str);
				retVal = false;
			}
		}

		if (retVal) {
			retVal = lstTables.isEmpty();
			if (!retVal) {

				// At this point there are more tables in the database than what we verified. We need
				// to see if all of these are temporary tables.

				qbuStringList lstLeftOver = lstTables;

				// Scan to see if all items left are temporary tables.
				foreach(QString str,lstLeftOver) {
					if (str.startsWith("_tmp",Qt::CaseInsensitive)) {
						lstTemp.append(str);
						lstTables.removeAll(str,Qt::CaseInsensitive);
					}
				}

				// Ignore the non removable SQLITE analyze/statistics table
				lstTables.removeAll("sqlite_stat1",Qt::CaseInsensitive);

				// Now if there are any tables left in lstTables we should have verified them..

				retVal = lstTables.isEmpty();
			}
		}

		if (!retVal) {
			std::cerr << "Verify coverage test failed" << std::endl;
			std::cerr << "Tables that failed verify: " << qPrintable(lstFailed.toCSVString()) << std::endl;
			std::cerr << "Tables that were not in the database but verified in code: " << qPrintable(lstExtra.toCSVString()) << std::endl;
			std::cerr << "Temp tables that were in the db but not verified: " << qPrintable(lstTemp.toCSVString()) << std::endl;
			std::cerr << "Regular tables that were in the db but not verified: " << qPrintable(lstTables.toCSVString()) << std::endl;
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDatabase::createTemporaryViews( qbuData* pData )
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member fixes known bad data in the database.
 *
 *	\details
 *	The base class implementation does nothing override in the child to perform  fixes 
 *	for a specific database.
 *
 */

bool qbuDatabase::fixKnownProblems()
{
	return true;
}

