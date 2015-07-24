#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuInsertQuery.h"
#include "qbuDataBase/qbuException.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuDataBase/qbuTable.h"
#include "qbuDataBase/qbuSelectQuery.h"
#include "qbuBase/qbuStringList.h"
#include "qbuDataBase/qbuDBColumnDef.h"
#include "qbuDataBase/qbuDBColumnDefList.h"
#include "qbuDataBase/qbuDatabaseFunctions.h"
#include "qbuLog/qbuLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuInsertQuery::qbuInsertQuery(std::shared_ptr<QSqlDatabase> pDB) : Superclass(pDB)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuInsertQuery::~qbuInsertQuery()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

QString generateInsertString(QStringList lst, QString strPrepend)
{
	QString retVal;
	bool bFirst = true;
	foreach(QString str, lst) {
		retVal += strPrepend + str;
		if (bFirst) {
			bFirst = false;
			strPrepend.prepend(", ");
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuInsertQuery::create(qbuPropertyMap* pData, qbuTable* pTable,
	smdb::InsertMode im /*= IM_NO_EXTRA_HANDLING*/)
{
	bool retVal = ((pData != nullptr) && (pTable != nullptr));
	if (retVal) {

		QStringList lst;

		qbuPropertyMap::iterator it = pData->begin();
		for (; it != pData->end(); ++it) {
			qbuProperty* pProp = *it;
			QString strName = pProp->objectName();
			if (pTable->isValidField(strName)) {
				lst.push_back(strName);
			}
		}

		retVal = !lst.isEmpty();
		if (retVal) {

			// The following will insert data into the table with an INSERT INTO query
			// This code was patterned after the following Qt example.
			//
			//  QSqlQuery query;
			//  query.prepare("INSERT INTO person (id, forename, surname) "
			//	"VALUES (:id, :forename, :surname)");
			//  query.bindValue(":id", 1001);
			//  query.bindValue(":forename", "Bart");
			//  query.bindValue(":surname", "Simpson");
			//  query.exec();

			QString strInsert;

			strInsert = handleInsertMode(im);

			strInsert += pTable->getTableName();
			strInsert += " (" + generateInsertString(lst, "") + ") ";

			strInsert += "VALUES (" + generateInsertString(lst, ":") + "); ";

			retVal = prepare(strInsert);
			if (retVal) {
				for (it = pData->begin(); it != pData->end(); ++it) {
					qbuProperty* pProp = *it;
					QString strName = pProp->objectName();
					if (pTable->isValidField(strName)) {
						strName.prepend(":");

						QVariant vt = pProp->GetData();
						//The following code converts bools to 1 or 0 for SQLITE
						//without this conversion the text "true" or "false" would be inserted 
						//in the database.

						if (vt.type() == QVariant::Bool) {
							vt = vt.toBool() ? QVariant(int(1)) : QVariant(int(0));
						}

						bindValue(strName, vt);
					}
				}
			}
			else
			{
				QLOG_CRIT() << QBULOG_DATABASE_TYPE << QString("An insert query for table %1 failed to prepare. Data will not make it to the database").arg(pTable->getTableName());
			}
		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuInsertQuery::create(qbuSelectQuery* pQuery, qbuTable* pTable,
	smdb::InsertMode im /*= smdb::IM_NO_EXTRA_HANDLING */)
{
	QString strInsert;
	bool retVal = generateQueryString(strInsert, pQuery, pTable, im);
	if (retVal) {
		retVal = exec(strInsert);

		if (!retVal) {
			QString strError = QString("Failed to insert into table %1. The database error message was %2.")
				.arg(pTable->getTableName())
				.arg(lastError().text());

#ifdef QBU_HAVE_EXCEPTIONS
			throw smException(__FILE__, __LINE__, qPrintable(strError), "qbuInsertQuery::create");
#else
			qDebug() << qPrintable(strError);
#endif //def QBU_HAVE_EXCEPTIONS
		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief
*	This member generates the proper SQL INSERT command for the smdb::InsertMode im.
*/

QString qbuInsertQuery::handleInsertMode(smdb::InsertMode im)
{
	QString retVal;
	switch (im) {
	default:
	case smdb::IM_NO_EXTRA_HANDLING:
		retVal = QString("INSERT INTO ");
		break;
	case smdb::IM_ROLLBACK:
		retVal = QString("INSERT OR ROLLBACK INTO ");
		break;
	case smdb::IM_ABORT:
		retVal = QString("INSERT OR ABORT INTO ");
		break;
	case smdb::IM_REPLACE:
		retVal = QString("INSERT OR REPLACE INTO ");
		break;
	case smdb::IM_IGNORE:
		retVal = QString("INSERT OR IGNORE INTO ");
		break;
	case smdb::IM_FAIL:
		retVal = QString("INSERT OR FAIL INTO ");
		break;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief
*	This generates a query string for the insert.
*	\details
*	Instead of using the built in Qt database inserting using bound values this query
*	generates a SQL string that can be executed directly with the values in the string.
*
*/

bool qbuInsertQuery::generateQueryString(QString & strInsert, qbuPropertyMap* pData,
	qbuTable* pTable,
	smdb::InsertMode im /*= smdb::IM_NO_EXTRA_HANDLING*/)
{
	bool retVal = ((pData != nullptr) && (pTable != nullptr));
	if (retVal) {

		QStringList lst;

		qbuPropertyMap::iterator it = pData->begin();
		for (; it != pData->end(); ++it) {
			qbuProperty* pProp = *it;
			QString strName = pProp->objectName();
			if (pTable->isValidField(strName)) {
				lst.push_back(strName);
			}
		}

		retVal = !lst.isEmpty();
		if (retVal) {
			strInsert = handleInsertMode(im);

			strInsert += pTable->getTableName();
			strInsert += " (" + generateInsertString(lst, "") + ") ";

			strInsert += "VALUES ( ";
			bool bFirst = true;
			for (it = pData->begin(); it != pData->end(); ++it) {
				qbuProperty* pProp = *it;
				QString strName = pProp->objectName();
				if (pTable->isValidField(strName)) {
					if (!bFirst) {
						strInsert += ", ";
					}
					else
					{
						bFirst = false;
					}

					QVariant vt = pProp->GetData();
					strInsert += toQueryValue(vt);

				}
			}
			strInsert += " ); ";
		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*	\brief
*	This member generates the insert query string for the query in pQuery into
*	the table pTable.
*
*	\details
*	@param strInsertQuery is the returned query.
*/

bool qbuInsertQuery::generateQueryString(QString & strInsertQuery, qbuSelectQuery* pQuery,
	qbuTable* pTable,
	smdb::InsertMode im /*= smdb::IM_NO_EXTRA_HANDLING */)
{
	bool retVal = (pQuery != nullptr);
	if (retVal) {
		QString strSQL;
		retVal = pQuery->generateSQL(strSQL);
		if (retVal) {
			// BUG_FIX: DO not use the dangerous call below..
			//retVal = generateQueryString(strInsertQuery,strSQL,pTable->getTableName(),im);

			QString strInsert;
			strInsert = handleInsertMode(im);
			strInsert += pTable->getTableName();

			qbuDBColumnDefList* pList = pQuery->getSelectFields();
			retVal = (pList != nullptr);
			if (retVal) {

				qbuStringList sl;

				// Get the header names from the qbuSelectQuery
				foreach(qbuDBColDef colDef, *pList) {
					if (!colDef.isExpression()) {
						sl.push_back(colDef.getNameOnly());
					}
					else
					{
						QString str = colDef.getAlias();
						retVal = (!str.isEmpty());
						if (retVal) {
							sl.push_back(str);
						}
						else
						{
							QString strMessage = QString("Please make sure the following expression has an alias: %1").append(colDef.getNameOnly());
							QLOG_WARN() << QBULOG_DATABASE_TYPE << strMessage;
							break;
						}

					}

				}

				strInsert += QString(" ( %1 ) %2 ; ").arg(sl.toCSVString()).arg(strSQL);

				strInsertQuery = strInsert;
			}
		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuInsertQuery::generateQueryString(QString & strInsertQuery,
	QString strQuery,
	QString strTable,
	smdb::InsertMode im /*= smdb::IM_NO_EXTRA_HANDLING */)
{
	bool retVal = (!strQuery.isEmpty() && !strTable.isEmpty());
	if (retVal) {
		QString strInsert;
		strInsert = handleInsertMode(im);
		strInsert += strTable;

		strInsert += QString(" %1 ; ").arg(strQuery);

		strInsertQuery = strInsert;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////