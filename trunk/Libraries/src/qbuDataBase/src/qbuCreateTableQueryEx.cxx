#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuCreateTableQueryEx.h"
#include "qbuDataBase/qbuDBColumnDefList.h"
#include "qbuDataBase/qbuSelectQuery.h"
#include "qbuDataBase/qbuCTSQLColumn.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuCreateTableQueryEx::qbuPrivate
{
public:
	QStringList getColumnNames(qbuCreateTableQueryEx* pPublic);

};

/////////////////////////////////////////////////////////////////////////////////////////

QStringList qbuCreateTableQueryEx::qbuPrivate::getColumnNames(qbuCreateTableQueryEx* pPublic)
{
	QStringList retVal;

	if (pPublic != nullptr) {
		sqlColumnList* pColList = pPublic->getColumnList();
		if (pColList != nullptr) {
			foreach(auto& column, *pColList)	{
				retVal << column.m_strColumnName;
			}
		}

	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuCreateTableQueryEx::qbuCreateTableQueryEx(std::shared_ptr<QSqlDatabase> pDB) : Superclass(pDB), 
m_pPrivate( new qbuPrivate )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuCreateTableQueryEx::~qbuCreateTableQueryEx()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuCreateTableQueryEx::createFromSelect(qbuSelectQuery & query)
{
	bool retVal;

	qbuDBColumnDefList* pFields = query.getSelectFields();
	
	retVal = (pFields != nullptr);
	if (retVal) {
		foreach(auto field, *pFields) {
			QString strName = field.m_strName;
			if (!doesColumnExist(strName)) {
				retVal = addColumn(strName, getExpectedTypeFromColumnName(strName));
				if (!retVal) {
					break;
				}
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuCreateTableQueryEx::getExpectedTypeFromColumnName(QString strName)
{
	QString retVal = "TEXT";

	strName = strName.trimmed();

	if (strName.endsWith("ID")) {
		retVal = "INTEGER";
	}
	else if (strName.endsWith("Date",Qt::CaseInsensitive)) {
		retVal = "DATETIME";
	}
	else if (strName.endsWith("Show", Qt::CaseInsensitive) || strName.endsWith("Completed", Qt::CaseInsensitive)) {
		retVal = "BOOLEAN";
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuCreateTableQueryEx::generateCreateAndInsertQueriesFromSelect(qbuSelectQuery & query, 
	QString strTableName, QString & strCreateTable, QString & strInsertData)
{
	bool retVal = createFromSelect(query);

	if (retVal) {
		strCreateTable = QString("CREATE TABLE %1 %2;").arg(strTableName).arg(generateColumnsQueryString());

		QString strSQL;

		retVal = query.generateSQL(strSQL);

		if (retVal) {
			strInsertData = QString("INSERT INTO %1 (%2) %3;")
				.arg(strTableName)
				.arg(m_pPrivate->getColumnNames(this).join(','))
				.arg(strSQL);
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
