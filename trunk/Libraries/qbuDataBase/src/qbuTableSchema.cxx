#include "qbuDBBasePCH.h"
#include "qbuTableSchema.h"
#include "qbuSelectQuery.h"
#include "qbuTable.h"
#include "qbuDatabase.h"
#include "smException.h"

#include <QSqlRecord>
#include <QStringList>
#include <iostream>
#include "qbuStringList.h"
#include "smLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuTableSchema::qbuTableSchema( qbuTable* pTable ) : m_pTable(pTable)
{

}

/*
bool qbuSelectQuery::getRecord( qbuPropertyMap* pPropMap )
{
	bool retVal = (m_pPrivate != NULL) && (pPropMap != NULL);
	if (retVal) {
		retVal = isValid();
		if (retVal) {
			int nField=0;
			foreach(qbuDBColDef col,m_pPrivate->m_lstSelect) {
				if (!isNull(nField)) {
					QTUTILS::Property prop;
					prop.setObjectName(col.getNameOrAlias());
					prop.SetData(value(nField));

					pPropMap->insert(prop);
				}
				nField++;
			}
		}
	}
	return retVal;
}

*/

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	Analyze table will query the database engine for the table schema and put the
 *	result in the m_lstColumns variable.
 */

bool qbuTableSchema::analyzeTable()
{
	bool retVal = (m_pTable != NULL);
	if (retVal) {
		qbuQuery query(*m_pTable->m_pDB);
		QString strQuery = QString("PRAGMA table_info(%1);").arg(m_pTable->getTableName());
		retVal = query.prepare(strQuery);
		if (retVal) {

			m_lstColumns.clear();

			retVal = (query.exec());
			if (retVal) {
				while (query.next() && retVal) {
					qbuTableColumnDef info;
					QSqlRecord record = query.record();
					int nIndex = record.indexOf("Name");
					if (nIndex >= 0) {
						info.setName(record.value(nIndex).toString());
					}

					nIndex = record.indexOf("Type");
					if (nIndex >= 0) {
						info.setType(record.value(nIndex).toString());
					}

					nIndex = record.indexOf("notnull");
					if (nIndex >= 0) {

					}

					if (!info.empty()) {
						m_lstColumns.push_back(info);
					}
				}
			}
		}
		else
		{

			QString strError = QString("ERROR: Failed prepare a query %1 %2")
				.arg(strQuery)
				.arg(query.lastError().text());

			QLOG_CRIT() << qPrintable(strError);

#ifdef QBU_HAVE_EXCEPTIONS
			throw smException(__FILE__,__LINE__,qPrintable(strError),"qbuSelectQuery::generateQuery");
#endif //def QBU_HAVE_EXCEPTIONS

		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTableSchema::verifyTable( qbuInfo* pInfo )
{
	bool retVal = (pInfo != NULL);
	qbuStringList lst = pInfo->getDBFieldNames();

	QStringList				lstMissing;
	qbuTableColumnDefList	lstCurrent = m_lstColumns;
	qbuTableColumnDefList	lstExtra;

	// Note: We still want to verify if the counts are different so that we can produce debug output.
	retVal = ((lst.count() > 0) ||  (m_lstColumns.count() > 0) );
	if (retVal) {
		qbuTableColumnDefList::iterator it = m_lstColumns.begin();
		for(; it != m_lstColumns.end(); ++it ) {
			QString strName;
			bool bFound = (it->getName(strName));
			
			if (bFound) {
				bFound = (lst.contains(strName,Qt::CaseInsensitive));
				if (bFound) {
					lst.removeAll(strName,Qt::CaseInsensitive);
				}
			}
			if (!bFound) {
				it->Print(std::cerr);
				lstExtra.push_back(*it);
			}
		}

		retVal = (lst.empty() && lstExtra.empty());
		if (!retVal) {
			QString strError = QString("qbuTableSchema::verifyTable failed for the table %1 ").arg(m_pTable->getTableName());
			if (!lst.empty()) {
				strError += "\nThe database table is missing the following columns that are in the info class: " + lst.toCSVString();
			}
			if (!lstExtra.empty()) {
				strError += "\nThe database table has the following columns that are not in the info class: ";
				foreach(qbuTableColumnDef col,lstExtra) {
					QString strName;
					if (col.getName(strName)) {
						strError += strName + " ";
					}
				}
				
			}
			//strError += "\nqbuTableSchema::verifyTable end " + m_pTable->getTableName();
			QLOG_CRIT() << qPrintable(strError);
		}
	}
	return retVal;
}

