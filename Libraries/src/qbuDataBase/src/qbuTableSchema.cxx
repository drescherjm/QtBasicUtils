#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuTableSchema.h"
#include "qbuDataBase/qbuSelectQuery.h"
#include "qbuDataBase/qbuTable.h"
#include "qbuDataBase/qbuDatabase.h"

#include "qbuBase/qbuStringList.h"
#include "qbuLog/qbuLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuTableSchema::qbuTableSchema( qbuTable* pTable ) : m_pTable(pTable)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	Analyze table will query the database engine for the table schema and put the
 *	result in the m_lstColumns variable.
 */

bool qbuTableSchema::analyzeTable()
{
	bool retVal = (m_pTable != nullptr);
	if (retVal) {
		qbuQuery query(m_pTable->m_pDB);
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

			QLOG_CRIT() << QBULOG_DATABASE_TYPE << qPrintable(strError);

#ifdef QBU_DB_USES_EXCEPTIONS
			throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuSelectQuery::generateQuery");
#else //def QBU_DB_USES_EXCEPTIONS
			
			databaseError(strError);

#endif //def QBU_DB_USES_EXCEPTIONS

		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuTableSchema::verifyTable( qbuInfo* pInfo )
{
	bool retVal = (pInfo != nullptr);
	if (retVal) {
		qbuStringList lst = pInfo->getDBFieldNames();

		QStringList				lstMissing;
		qbuTableColumnDefList	lstCurrent = m_lstColumns;
		qbuTableColumnDefList	lstExtra;

		// Note: We still want to verify if the counts are different so that we can produce debug output.
		retVal = ((lst.count() > 0) || (m_lstColumns.count() > 0));
		if (retVal) {
			qbuTableColumnDefList::iterator it = m_lstColumns.begin();
			for (; it != m_lstColumns.end(); ++it) {
				QString strName;
				bool bFound = (it->getName(strName));

				if (bFound) {
					bFound = (lst.contains(strName, Qt::CaseInsensitive));
					if (bFound) {
						lst.removeAll(strName, Qt::CaseInsensitive);
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
					foreach(qbuTableColumnDef col, lstExtra) {
						QString strName;
						if (col.getName(strName)) {
							strError += strName + " ";
						}
					}

				}
				//strError += "\nqbuTableSchema::verifyTable end " + m_pTable->getTableName();
				QLOG_CRIT() << QBULOG_DATABASE_TYPE << qPrintable(strError);
			}
			if (retVal) {
				QSet<QString> setRequired = m_pTable->getRequiredFieldList().toSet();
				if (!setRequired.isEmpty()) {
					setRequired.subtract(pInfo->getDBFieldNames().toSet());

					retVal = setRequired.isEmpty();
					if (!retVal) {
						QString strError = QString("qbuTableSchema::verifyTable failed for the table %1 ").arg(m_pTable->getTableName());
						strError += "\nThe database has the following columns listed as required but they are not in the info class: ";
						foreach(QString strField, setRequired) {
							strError += strField + " ";
						}	
						QLOG_CRIT() << QBULOG_DATABASE_TYPE << qPrintable(strError);
					}
				
				}
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuTableSchema::databaseError(QString strErrorMessage)
{
	if (m_pTable && m_pTable->m_pDB) {
		m_pTable->m_pDB->emitDatabaseError(strErrorMessage);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

