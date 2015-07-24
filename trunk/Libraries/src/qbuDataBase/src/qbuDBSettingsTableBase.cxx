#include "qbuDatabasePCH.h"
#include "qbuDataBase/qbuDBSettingsTableBase.h"
#include "qbuDataBase/qbuDatabase.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuDataBase/qbuSelectQuery.h"
#include "qbuDataBase/qbuDBSettingInfo.h"
#include "qbuDataBase/qbuCreateTableQuery.h"
//#include "qbuDataBase/qbuConstants.h"

/////////////////////////////////////////////////////////////////////////////////////////

const QString qbuDBSettingsTableBase::g_strTable("DBSettings");

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBSettingsTableBase::qbuDBSettingsTableBase( std::shared_ptr<qbuDatabase> pDB ) : Superclass(pDB)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::createTable( int nSchema )
{
	bool retVal = (m_pDB != nullptr);
	if (retVal) {

		qbuCreateTableQuery query(m_pDB);
		query.addPKColumn(qbuDBSettingInfo::g_strSettingName,QString("TEXT"),QString("NOT NULL"));
		query.addColumn(qbuDBSettingInfo::g_strSettingValue,QString("TEXT"));

		retVal = internalCreateTable(getTableName(),query.generateColumnsQueryString());
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::upgradeTable( int nOldSchema, int nNewSchema )
{
	bool retVal = Superclass::upgradeTable(nOldSchema,nNewSchema);
	if (retVal) {
		retVal = ((nOldSchema == nNewSchema));
		if (!retVal) {
			// Here we make sure that the other params are synced to the database.
			
			retVal = true;

// 			int nRecent = getMinimumDaysBetweenViewingCase();
// 			if (nRecent < 0) {
// 				retVal = setMinimumDaysBetweenViewingCase(nRecent);
// 			}
			
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::insertInitialValues( int nSchema )
{
	bool retVal = true;

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBSettingsTableBase::getTableName() const
{
	return g_strTable;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::addSetting( qbuDBSettingInfo* pSettingInfo )
{
	return insertData(pSettingInfo);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::lookupSetting( qbuDBSettingInfo* pSettingInfo )
{

	
#if 0
	bool retVal = (pRatingTypeInfo != nullptr) && (pRatingTypeInfo->hasField(smRatingTypeInfo::g_strRatingTypeID));
	if (retVal) {

		quint8 nRatingTypeID;

		retVal = pRatingTypeInfo->getField(smRatingTypeInfo::g_strRatingTypeID,nRatingTypeID);

		if (retVal) {
			/*
			SELECT 'RatingTypeName', 'RatingTypeID' FROM RatingTypes WHERE
			TypeID = nRatingTypeID
			*/
			smSelectQuery query(m_pDB);
			query.addSelectField(smRatingTypeInfo::g_strRatingTypeName);
			query.addSelectField(smRatingTypeInfo::g_strRatingTypeID);
			query.addFromField(getTableName());
			query.setWhereClause(QString("%1 = %2")
				.arg(smRatingTypeInfo::g_strRatingTypeID)
				.arg(nRatingTypeID));

			retVal = query.generateQuery();
			if (retVal) {
				retVal = query.exec();
				if (retVal) {
					retVal = query.next();
					if (retVal) {
						retVal = query.getRecord(pRatingTypeInfo);
					}
				}
			}

		}


	}
	return retVal;
	
#endif

	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuInfo* qbuDBSettingsTableBase::createInfoClass() const
{
	return new InfoClass();
}

/////////////////////////////////////////////////////////////////////////////////////////

int qbuDBSettingsTableBase::getDBSchemaVersion()
{
	int retVal = -1;
	if (m_pDB->isOpen()) {
		QString strQuery = QString("SELECT Value FROM %1 WHERE Name = '%2'")
			.arg(g_strTable)
			.arg(getVariableName(SCHEMA_VERSION));
		qbuSimpleQuery query(strQuery,m_pDB);
		if (query.next()) {
			retVal = query.value(0).toInt();
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::setDBSchemaVersion( int nSchema )
{
	bool retVal = m_pDB->isOpen();
	if (retVal) {
		QString strQuery = QString("REPLACE into %1 (Name, Value) VALUES ('%3', %2)")
			.arg(g_strTable)
			.arg(nSchema)
			.arg(getVariableName(SCHEMA_VERSION));
		qbuSimpleQuery query(m_pDB);
		retVal = query.exec(strQuery);
		if(retVal)
		{
			qDebug() << "Schema updated to" << nSchema;
		}
		else
		{
			qDebug() << "ERRROR: Failed to update schema" << query.lastError();

		}

	}
	else
	{
		qDebug() << "ERROR: The database is not open." ;

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
 *	\brief
 *	The setup schema version is an additional schema that applies updates for a 
 *	specific study from the smSetupLib.
 *	\details
 *	Most of these smSetupLib updates should be related to database population and 
 *	minor changes to the database after the study has started. 
 */

int qbuDBSettingsTableBase::getSetupSchemaVersion()
{
	int retVal = -1;
	if (m_pDB->isOpen()) {
		QString strQuery = QString("SELECT Value FROM %1 WHERE Name = '%2'")
			.arg(g_strTable)
			.arg(getVariableName(SETUP_SCHEMA_VERSION));
		qbuSimpleQuery query(strQuery,m_pDB);
		if (query.next()) {
			retVal = query.value(0).toInt();
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::setSetupSchemaVersion( int nSchema )
{
	bool retVal = m_pDB->isOpen();
	if (retVal) {
		QString strQuery = QString("REPLACE into %1 (Name, Value) VALUES ('%3', %2)")
			.arg(g_strTable)
			.arg(nSchema)
			.arg(getVariableName(SETUP_SCHEMA_VERSION));
		qbuSimpleQuery query(m_pDB);
		retVal = query.exec(strQuery);
		if(retVal)
		{
			qDebug() << "The Setup schema updated to" << nSchema;
		}
		else
		{
			qDebug() << "ERRROR: Failed to update the setup schema" << query.lastError();

		}

	}
	else
	{
		qDebug() << "ERROR: The database is not open." ;

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int qbuDBSettingsTableBase::getMinimumDaysBetweenViewingCase()
{
	int retVal = -1;
	if (m_pDB->isOpen()) {
		QString strQuery = QString("SELECT Value FROM %1 WHERE Name = '%2'")
			.arg(g_strTable)
			.arg(getVariableName(CASE_LAST_SEEN_MINIMUM_DAYS));
		qbuSimpleQuery query(strQuery,m_pDB);
		if (query.next()) {
			retVal = query.value(0).toInt();
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::setMinimumDaysBetweenViewingCase( quint8 nDays )
{
	bool retVal = m_pDB->isOpen();
	if (retVal) {

		QString strVar = getVariableName(CASE_LAST_SEEN_MINIMUM_DAYS);
		retVal = !strVar.isEmpty();
		if (retVal) {
			QString strQuery = QString("REPLACE into %1 (Name, Value) VALUES ('%2', %3)")
				.arg(g_strTable)
				.arg(strVar)
				.arg(nDays);
			qbuSimpleQuery query(m_pDB);
			retVal = query.exec(strQuery);
			if(retVal)
			{
				qDebug() << strVar << " updated to" << nDays;
			}
			else
			{
				qDebug() << "ERRROR: Failed to update " << strVar << " " << query.lastError();

			}
		}
	}
	else
	{
		qDebug() << "ERROR: The database is not open." ;

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBSettingsTableBase::getVariableName( int nVariable )
{
	QString retVal;
	switch (nVariable) {
		case SCHEMA_VERSION:
			retVal = QString("SCHEMA_VERSION");
			break;
		case CASE_LAST_SEEN_MINIMUM_DAYS:
			retVal = QString("CASE_LAST_SEEN_MINIMUM_DAYS");
			break;
		case ALLOW_TRUTH_ENTRY:
			retVal = QString("ALLOW_TRUTH_ENTRY");
			break;
		case CASE_VIEW_TIMEOUT_IGNORE_CASE_COUNT:
			retVal = QString("CASE_VIEW_TIMEOUT_IGNORE_CASE_COUNT");
			break;
		case SETUP_SCHEMA_VERSION:
			retVal = QString("SETUP_SCHEMA_VERSION");
			break;
		case ALLOW_READER_REVIEW:
			retVal = QString("ALLOW_READER_REVIEW");
			break;
		case READER_DEFAULT_PASSWORD:
			retVal = QString("READER_DEFAULT_PASSWORD");
			break;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::getAllowTruthEntry()
{
	bool retVal = false;
	if (m_pDB->isOpen()) {
		QString strQuery = QString("SELECT Value FROM %1 WHERE Name = '%2'")
			.arg(g_strTable)
			.arg(getVariableName(ALLOW_TRUTH_ENTRY));
		qbuSimpleQuery query(strQuery,m_pDB);
		if (query.next()) {
			retVal = (query.value(0).toInt() != 0);
		}
		else
		{
			setAllowTruthEntry(false);
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::setAllowTruthEntry( bool bAllow )
{
	bool retVal = m_pDB->isOpen();
	if (retVal) {

		QString strVar = getVariableName(ALLOW_TRUTH_ENTRY);
		retVal = !strVar.isEmpty();
		if (retVal) {
			QString strQuery = QString("REPLACE into %1 (Name, Value) VALUES ('%2', %3)")
				.arg(g_strTable)
				.arg(strVar)
				.arg(bAllow ? 1 :0);
			qbuSimpleQuery query(m_pDB);
			retVal = query.exec(strQuery);
		}
	}
	else
	{
		qDebug() << "ERROR: The database is not open." ;

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::getAllowReaderReview()
{
	bool retVal = false;
	if (m_pDB->isOpen()) {
		QString strQuery = QString("SELECT Value FROM %1 WHERE Name = '%2'")
			.arg(g_strTable)
			.arg(getVariableName(ALLOW_READER_REVIEW));
		qbuSimpleQuery query(strQuery,m_pDB);
		if (query.next()) {
			retVal = (query.value(0).toInt() != 0);
		}
		else
		{
			setAllowReaderReview(false);
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::setAllowReaderReview( bool bAllow )
{
	bool retVal = m_pDB->isOpen();
	if (retVal) {

		QString strVar = getVariableName(ALLOW_READER_REVIEW);
		retVal = !strVar.isEmpty();
		if (retVal) {
			QString strQuery = QString("REPLACE into %1 (Name, Value) VALUES ('%2', %3)")
				.arg(g_strTable)
				.arg(strVar)
				.arg(bAllow ? 1 :0);
			qbuSimpleQuery query(m_pDB);
			retVal = query.exec(strQuery);
		}
	}
	else
	{
		qDebug() << "ERROR: The database is not open." ;

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSettingsTableBase::setNumberOfCompletedCasesToIgnoreViewTimeout( uint8_t nCases )
{
	bool retVal = m_pDB->isOpen();
	if (retVal) {

		QString strVar = getVariableName(CASE_VIEW_TIMEOUT_IGNORE_CASE_COUNT);
		retVal = !strVar.isEmpty();
		if (retVal) {
			QString strQuery = QString("REPLACE into %1 (Name, Value) VALUES ('%2', %3)")
				.arg(g_strTable)
				.arg(strVar)
				.arg(nCases);
			qbuSimpleQuery query(m_pDB);
			retVal = query.exec(strQuery);
			if(retVal)
			{
				qDebug() << strVar << " updated to" << nCases;
			}
			else
			{
				qDebug() << "ERRROR: Failed to update " << strVar << " " << query.lastError();

			}
		}
	}
	else
	{
		qDebug() << "ERROR: The database is not open." ;

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

uint8_t qbuDBSettingsTableBase::getNumberOfCompletedCasesToIgnoreViewTimeout()
{
	uint8_t retVal = 0;
	if (m_pDB->isOpen()) {
		QString strQuery = QString("SELECT Value FROM %1 WHERE Name = '%2'")
			.arg(g_strTable)
			.arg(getVariableName(CASE_VIEW_TIMEOUT_IGNORE_CASE_COUNT));
		qbuSimpleQuery query(strQuery,m_pDB);
		if (query.next()) {
			retVal = query.value(0).toUInt();
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuDBSettingsTableBase::getReaderDefaultPIN()
{
	QString retVal("2513");
	if (m_pDB->isOpen()) {
		QString strQuery = QString("SELECT Value FROM %1 WHERE Name = '%2'")
			.arg(g_strTable)
			.arg(getVariableName(READER_DEFAULT_PASSWORD));
		qbuSimpleQuery query(strQuery, m_pDB);
		if (query.next()) {
			retVal = query.value(0).toString();
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////