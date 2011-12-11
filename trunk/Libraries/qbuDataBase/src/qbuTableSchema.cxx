#include "smDBBasePCH.h"
#include "smTableSchema.h"
#include "smSelectQuery.h"
#include "smTable.h"
#include "smDatabase.h"
#include "smException.h"

#include <QSqlRecord>
#include <QStringList>
#include <iostream>
#include "smStringList.h"
#include "smLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

smTableSchema::smTableSchema( smTable* pTable ) : m_pTable(pTable)
{

}

/*
bool smSelectQuery::getRecord( smPropertyMap* pPropMap )
{
	bool retVal = (m_pPrivate != NULL) && (pPropMap != NULL);
	if (retVal) {
		retVal = isValid();
		if (retVal) {
			int nField=0;
			foreach(smDBColDef col,m_pPrivate->m_lstSelect) {
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

bool smTableSchema::analyzeTable()
{
	bool retVal = (m_pTable != NULL);
	if (retVal) {
		smQuery query(*m_pTable->m_pDB);
		QString strQuery = QString("PRAGMA table_info(%1);").arg(m_pTable->getTableName());
		retVal = query.prepare(strQuery);
		if (retVal) {

			m_lstColumns.clear();

			retVal = (query.exec());
			if (retVal) {
				while (query.next() && retVal) {
					smTableColumnDef info;
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

#ifdef SM_HAVE_EXCEPTIONS
			throw smException(__FILE__,__LINE__,qPrintable(strError),"smSelectQuery::generateQuery");
#endif //def SM_HAVE_EXCEPTIONS

		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smTableSchema::verifyTable( smInfo* pInfo )
{
	bool retVal = (pInfo != NULL);
	smStringList lst = pInfo->getDBFieldNames();

	QStringList				lstMissing;
	smTableColumnDefList	lstCurrent = m_lstColumns;
	smTableColumnDefList	lstExtra;

	// Note: We still want to verify if the counts are different so that we can produce debug output.
	retVal = ((lst.count() > 0) ||  (m_lstColumns.count() > 0) );
	if (retVal) {
		smTableColumnDefList::iterator it = m_lstColumns.begin();
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
			QString strError = QString("smTableSchema::verifyTable failed for the table %1 ").arg(m_pTable->getTableName());
			if (!lst.empty()) {
				strError += "\nThe database table is missing the following columns that are in the info class: " + lst.toCSVString();
			}
			if (!lstExtra.empty()) {
				strError += "\nThe database table has the following columns that are not in the info class: ";
				foreach(smTableColumnDef col,lstExtra) {
					QString strName;
					if (col.getName(strName)) {
						strError += strName + " ";
					}
				}
				
			}
			//strError += "\nsmTableSchema::verifyTable end " + m_pTable->getTableName();
			QLOG_CRIT() << qPrintable(strError);
		}
	}
	return retVal;
}

