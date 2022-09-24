#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuTable.h"
#include "qbuDataBase/qbuDatabase.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuDataBase/qbuTableSchema.h"
#include "qbuBase/qbuStringList.h"
#include "qbuDataBase/qbuSelectQuery.h"
#include "qbuBase/qbuProperty.h"
#include "qbuLog/qbuLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuTable::qbuTable(std::shared_ptr<qbuDatabase> pDataBase) : m_pDB(pDataBase)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuTable::~qbuTable()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief
*	This is the base upgradeTable.
*	\details
*	This function checks if the table needs to be created. If so it does and calls
*  qbuTable::insertInitialValues(int nSchema) to insert these initial values.
*/

bool qbuTable::upgradeTable(int nOldSchema, int nNewSchema)
{
	bool retVal = m_pDB->tableExists(getTableName());
	if (!retVal) {
		retVal = createTable(nNewSchema);
		if (retVal) {
			retVal = insertInitialValues(nNewSchema);
			if (!retVal) {

				QString strError = QString("ERROR: Could not initialize table %1")
					.arg(getTableName());

				QLOG_CRIT() << QBULOG_DATABASE_TYPE << strError;

#ifdef QBU_DB_USES_EXCEPTIONS
				throw qbuException(__FILE__, __LINE__, qPrintable(strError), "qbuTable::upgradeTable");

#else // def QBU_DB_USES_EXCEPTIONS

				databaseError(strError);

#endif //def QBU_DB_USES_EXCEPTIONS

			}
		}
	}
	if (retVal) {
		QLOG_INFO() << QBULOG_DATABASE_TYPE << QString("The table %1 was upgraded to schema %2").arg(getTableName()).arg(nNewSchema);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::insertData(qbuPropertyMap* pData, qbudb::InsertMode im /*= IM_NO_EXTRA_HANDLING*/)
{
	bool retVal = (pData != nullptr);

	if (retVal) {
		qbuInsertQuery query(m_pDB);
		retVal = query.create(pData, this, im);
		if (retVal) {
			retVal = query.exec();
			if (!retVal) {
				// 


				QString strError = QString("Failed to insert data into the table %1. "
					"Using the following query: \n").arg(getTableName());

				QTextStream stream(&strError);

				//QLOG_CRIT() << QBULOG_DATABASE_TYPE << strError;

				QString str;
				if (query.generateQueryString(str, pData, this, im)) {
					stream << str << "\n";
				}
				else
				{
					stream << query.executedQuery() << "\n";
				}
				
				//QLOG_CRIT() << QBULOG_DATABASE_TYPE << str;


				QSqlError error = query.lastError();

				stream << error.text() << "\n";

				pData->Print(stream);
				
				QLOG_CRIT() << QBULOG_DATABASE_TYPE << strError;

			}
		}

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::isValidField(QString strName)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief
*	This member creates the table in the database using a CREATE TABLE SQL command.
*/

bool qbuTable::internalCreateTable(QString strTableName, QString strTableSQL)
{
	bool retVal = (m_pDB != nullptr) && (m_pDB->isOpen());
	if (retVal) {
		QString	CREATE_TABLE = QString("CREATE TABLE %1 %2").arg(strTableName).arg(strTableSQL);
		qbuSimpleQuery	query(m_pDB);

		CREATE_TABLE = CREATE_TABLE.trimmed();

		if (!CREATE_TABLE.endsWith(";")) {
			CREATE_TABLE.append(";");
		}

		retVal = query.exec(CREATE_TABLE);
		if (retVal)
		{
			QString strMsg = QString("The table %1 was created.").arg(strTableName);
			QLOG_INFO() << QBULOG_DATABASE_TYPE << strMsg;
		}
		else
		{
			QString strError = QString("%1 %2 %3")
				.arg("Failed to create table")
				.arg(strTableName)
				.arg(query.lastError().text());


			QLOG_CRIT() << QBULOG_DATABASE_TYPE << strError;

#ifdef QBU_DB_USES_EXCEPTIONS
			throw qbuException(__FILE__, __LINE__, qPrintable(strError), "qbuTable::internalCreateTable");
#else // def QBU_DB_USES_EXCEPTIONS

		databaseError(strError);

#endif //def QBU_DB_USES_EXCEPTIONS

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief The purpose of the member function is to add a column to an existing table.
*/

bool qbuTable::addColumn(QString strCoumnName, QString strDataType, QString strConstraint/*=QString()*/)
{
	bool retVal = (m_pDB != nullptr) && (m_pDB->isOpen());
	if (retVal) {
		QString strSQL;
		strSQL = QString("ALTER TABLE %1 ADD COLUMN %2 %3 %4")
			.arg(getTableName())
			.arg(strCoumnName)
			.arg(strDataType)
			.arg(strConstraint);

		qbuSimpleQuery	query(m_pDB);

		retVal = query.exec(strSQL);
		if (retVal)
		{
			QLOG_INFO() << QBULOG_DATABASE_TYPE << "Column " << strCoumnName << " added to table " << getTableName();
		}
		else
		{
			QString strError = QString("Failed to add column %1 to table %2. The database error message was %3.")
				.arg(strCoumnName)
				.arg(getTableName())
				.arg(query.lastError().text());

			QLOG_CRIT() << QBULOG_DATABASE_TYPE << strError;

#ifdef QBU_DB_USES_EXCEPTIONS
			throw qbuException(__FILE__, __LINE__, qPrintable(strError), "qbuTable::addColumn");

#else // def QBU_DB_USES_EXCEPTIONS

			databaseError(strError);

#endif //def QBU_DB_USES_EXCEPTIONS

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::renameTable(QString strNewName)
{
	bool retVal = (m_pDB != nullptr) && (m_pDB->isOpen());
	if (retVal) {
		QString strSQL;
		strSQL = QString("ALTER TABLE %1 RENAME TO %2")
			.arg(getTableName())
			.arg(strNewName);

		qbuSimpleQuery	query(m_pDB);

		retVal = query.exec(strSQL);

		if (retVal)
		{
			QString strMsg = QString("The table %1 was renamed to %2").arg(getTableName()).arg(strNewName);
			QLOG_INFO() << QBULOG_DATABASE_TYPE << strMsg;
		}
		else
		{
			QString strError = QString("Failed to rename table %1 to %2. The database error message was %3.")
				.arg(getTableName())
				.arg(strNewName)
				.arg(query.lastError().text());


			QLOG_CRIT() << QBULOG_DATABASE_TYPE << strError;

#ifdef QBU_DB_USES_EXCEPTIONS
			throw qbuException(__FILE__, __LINE__, qPrintable(strError), "qbuTable::renameTable");

#else	// def QBU_DB_USES_EXCEPTIONS

			databaseError(strError);

#endif //def QBU_DB_USES_EXCEPTIONS

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

		std::unique_ptr<qbuInfo> ptr(createInfoClass());
		retVal = (ptr.get() != nullptr);
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

/**
*	\brief
*	This member function returns the list of optional Primary Keys.
*
*	\details
*	Optional Primary Keys will be set to the default value in insert queries. For
*	integer primary keys this value will most likely be -1.
*
*/

const QStringList& qbuTable::getOptionalPrimaryKeyList() const
{
	static QStringList lst;
	return lst;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::verifyRequiredFields(qbuInfo * pInfo, bool bWarn) const
{
	return verifyRequiredFields(pInfo, getRequiredFieldList(),bWarn);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTable::verifyRequiredFields(qbuInfo * pInfo, const QStringList & lstFields,bool bWarn) const
{
	bool retVal = (pInfo != nullptr);
	if (retVal) {
		qbuStringList lstMissingRequired;

		const QStringList& lst = lstFields;
		foreach(QString str, lst) {
			if (!pInfo->hasField(str)) {
				lstMissingRequired.push_back(str);
			}
		}

		retVal = lstMissingRequired.isEmpty();
		if (!retVal && bWarn) {

			QString strMessage = QString("A query on table %1 will fail because the "
				"following fields are not defined in the qbuInfo class (%2): %3")
				.arg(getTableName())
				.arg(pInfo->metaObject()->className())
				.arg(lstMissingRequired.toCSVString());

			QLOG_WARN() << QBULOG_DATABASE_TYPE << strMessage;
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

int qbuTable::count(QStringList lstWhereFields /* = QStringList() */, 
	qbuPropertyMap* pPropMap /* = nullptr */, 
	const qbuDBCondition & expr /* = qbuDBCondition() */, 
	const QStringList & lstSelectFields /* = QStringList() */)
{
	int retVal = -1;
	qbuSelectQuery query(m_pDB);

	QString strCountExpr;

	if (lstSelectFields.isEmpty()) {
		strCountExpr = "COUNT(*)";
	}
	else {
		strCountExpr = QString(" COUNT(%1) ").arg(lstSelectFields.join(", "));
	}

	// Setup a typical Count(*) query
	qbuDBColDef countval = qbuDBColDef(strCountExpr, qbuDBColDef::OP_IS_EXPRESSION).addAlias("Count");

	query.addSelectField(countval);
	query.addFromField(getTableName());

	// Add where expressions if necessary..
	if (pPropMap != nullptr) {
		query.appendWhereExpressions(lstWhereFields, pPropMap);
	}

	if (!expr.isEmpty()) {
		query.appendWhereExpression(expr);
	}
	
	// Now get the value of the count.
	if (query.generateQuery() && query.exec() && query.next()) {
		qbuPropertyMap ret;
		if (query.getRecord(&ret)) {
			ret.getField<int>("Count", retVal);
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int qbuTable::countDistinct(QStringList lstWhereFields /* = QStringList() */, 
	qbuPropertyMap* pPropMap /* = nullptr */, 
	const qbuDBCondition & expr /* = qbuDBCondition() */, 
	const QStringList & lstSelectFields /* = QStringList() */)
{
	int retVal = -1;
	qbuSelectQuery query(m_pDB);

	// Setup a typical Count(*) query
	qbuDBColDef countval = qbuDBColDef("COUNT(*)", qbuDBColDef::OP_IS_EXPRESSION).addAlias("Count");

	query.addSelectField(countval);

	qbuSelectQuery nested(m_pDB);

	if (lstSelectFields.isEmpty()) {
		nested.addSelectField("*");
	}
	else {
		nested.addSelectFields(lstWhereFields);
	}

	nested.setSelectOption(qbuSelectQuery::QBU_SELECT_DISTINCT);
	nested.addFromField(getTableName());

	// Add where expressions if necessary..
	if (pPropMap != nullptr) {
		nested.appendWhereExpressions(lstWhereFields, pPropMap);
	}

	if (!expr.isEmpty()) {
		query.appendWhereExpression(expr);
	}

	query.addFromField(nested, "T1");

	// Now get the value of the count.
	if (query.generateQuery() && query.exec() && query.next()) {
		qbuPropertyMap ret;
		if (query.getRecord(&ret)) {
			ret.getField<int>("Count", retVal);
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

std::pair<bool, QStringList> qbuTable::getCurrentTableColumnNames(const QStringList& filter)
{
	// This uses a SQLITE pragma function pragma_table_info('tableName') to get
	// the list of the columns in a database table.
	// See the doc here: https://www.sqlite.org/pragma.html

	std::pair<bool, QStringList> retVal;

	bool bFilter = !filter.isEmpty();

	qbuSelectQuery query(m_pDB);
	query.addSelectField("name");
	query.addFromField(QString("pragma_table_info('%1')").arg(getTableName()));

	retVal.first = query.generateQuery() && query.exec();
	if (retVal.first) {
		while (query.next() && retVal.first) {
			qbuPropertyMap ret;
			retVal.first = query.getRecord(&ret); 
			if (retVal.first) {
				QString strRow;
				retVal.first = ret.getField<QString>("name", strRow);
				if (retVal.first) {
					if (bFilter) {
						// Ignore if the string is not in the filter
						if (!filter.contains(strRow, Qt::CaseInsensitive)) {
							continue;
						}
					}
					retVal.second.push_back(strRow);
				}
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuTable::getUniqueTempTableName(QString strBase, int nIndexStart/*=0*/) const
{
	QString retVal = strBase;
	if (m_pDB->tableExists(retVal)) {
		for (int i = nIndexStart; i < 100 && m_pDB->tableExists(retVal); ++i) {
			retVal = QString("%1_v%2")
				.arg(strBase)
				.arg(i, 2, 10, QChar('0'));
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuTable::databaseError(QString strErrorMessage)
{
	if (m_pDB) {
		m_pDB->emitDatabaseError(strErrorMessage);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
