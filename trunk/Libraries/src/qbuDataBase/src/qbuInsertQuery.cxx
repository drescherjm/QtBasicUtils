#include "qbuInsertQuery.h"
#include "qbuException.h"
#include <QStringList>
#include "qbuPropertyMap.h"
#include "..\Include\qbuTable.h"
#include "..\..\qbuDatabase\qbuDatabasePCH.h"
#include "qbuSelectQuery.h"
#include "qbuStringList.h"
#include "qbuDBColumnDef.h"
#include "qbuDBColumnDefList.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuInsertQuery::qbuInsertQuery(QSqlDatabase db) : Superclass(db)
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
	foreach(QString str,lst) {
		retVal += strPrepend + str;
		if (bFirst) {
			bFirst = false;
			strPrepend.prepend(", ");
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuInsertQuery::create( qbuPropertyMap* pData,qbuTable* pTable,
						   smdb::InsertMode im /*= IM_NO_EXTRA_HANDLING*/ )
{
	bool retVal = ((pData != NULL) && (pTable != NULL));
	if (retVal) {

		QStringList lst;

		qbuPropertyMap::iterator it = pData->begin();
		for( ;it != pData->end();++it) {
			QTUTILS::Property* pProp = *it;
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
			strInsert += " (" + generateInsertString(lst,"") + ") ";

			strInsert += "VALUES (" + generateInsertString(lst,":") + "); ";

			prepare(strInsert);
			for(it = pData->begin() ;it != pData->end();++it) {
				QTUTILS::Property* pProp = *it;
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

					bindValue(strName,vt);
				}
			}

		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuInsertQuery::create( qbuSelectQuery* pQuery,qbuTable* pTable, 
						   smdb::InsertMode im /*= smdb::IM_NO_EXTRA_HANDLING */ )
{
	QString strInsert;
	bool retVal = generateQueryString(strInsert,pQuery,pTable,im);
	if (retVal) {
		retVal = exec(strInsert);

		if (!retVal) {
			QString strError = QString("Failed to insert into table %1. The database error message was %2.")
				.arg(pTable->getTableName())
				.arg(lastError().text());

#ifdef QBU_HAVE_EXCEPTIONS
			throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuInsertQuery::create");
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

QString qbuInsertQuery::handleInsertMode( smdb::InsertMode im )
{
	QString retVal;
	switch(im) {
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

bool qbuInsertQuery::generateQueryString( QString & strInsert, qbuPropertyMap* pData,
										qbuTable* pTable, 
										smdb::InsertMode im /*= smdb::IM_NO_EXTRA_HANDLING*/ )
{
	bool retVal = ((pData != NULL) && (pTable != NULL));
	if (retVal) {

		QStringList lst;

		qbuPropertyMap::iterator it = pData->begin();
		for( ;it != pData->end();++it) {
			QTUTILS::Property* pProp = *it;
			QString strName = pProp->objectName();
			if (pTable->isValidField(strName)) {
				lst.push_back(strName);
			}
		}

		retVal = !lst.isEmpty();
		if (retVal) {
			strInsert = handleInsertMode(im);

			strInsert += pTable->getTableName();
			strInsert += " (" + generateInsertString(lst,"") + ") ";

			strInsert += "VALUES ( ";
			bool bFirst = true;
			for(it = pData->begin() ;it != pData->end();++it) {
				QTUTILS::Property* pProp = *it;
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
					//The following code converts bools to 1 or 0 for SQLITE
					//without this conversion the text "true" or "false" would be inserted 
					//in the database.

					//strInsert += singleQuoteIfNecissary(vt.toString());

					strInsert += toQueryValue(vt);

					//strInsert += "\" " + vt.toString() + "\" ";
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

bool qbuInsertQuery::generateQueryString( QString & strInsertQuery, qbuSelectQuery* pQuery, 
										 qbuTable* pTable, 
										 smdb::InsertMode im /*= smdb::IM_NO_EXTRA_HANDLING */ )
{
	bool retVal = (pQuery != NULL);
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
			retVal = (pList != NULL);
			if (retVal) {

				qbuStringList sl;

				// Get the header names from the qbuSelectQuery
				foreach(qbuDBColDef colDef,*pList) {
					sl.push_back(colDef.getNameOnly());
				}

				strInsert += QString(" ( %1 ) %2 ; ").arg(sl.toCSVString()).arg(strSQL);

				strInsertQuery = strInsert;
			}
		}
		
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuInsertQuery::generateQueryString( QString & strInsertQuery, 
										 QString strQuery, 
										 QString strTable, 
										 smdb::InsertMode im /*= smdb::IM_NO_EXTRA_HANDLING */ )
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
