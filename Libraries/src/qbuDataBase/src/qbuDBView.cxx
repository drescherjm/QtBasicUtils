#include "qbuDatabasePCH.h"
#include "qbuDataBase/qbuDBView.h"
#include "qbuDataBase/qbuDatabase.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuBase/qbuException.h"
#include "qbuBase/qbuStringList.h"
#include "qbuDataBase/qbuCreateViewQuery.h"
#include "qbuDataBase/qbuSimpleQuery.h"
#include "qbuDataBase/qbuInfo.h"
#include "qbuLog/qbuLog.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBView::qbuDBView( std::shared_ptr<qbuDatabase> pDataBase ) : m_pDB(pDataBase)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This is the base upgradeDBView. 
 *	\details
 *	This function checks if the DBView needs to be created. If so it does and calls
 *  qbuDBView::insertInitialValues(int nSchema) to insert these initial values. 
 */

bool qbuDBView::upgradeDBView( int nOldSchema, int nNewSchema, bool bForceUpdate )
{
	bool retVal = m_pDB->viewExists(getDBViewName()) ;
	if (retVal) {
        if (viewNeedsUpdate(nOldSchema, nNewSchema, bForceUpdate)) {
            retVal = !dropView();
        }
	}
	if (!retVal) {
		retVal = createDBView( nNewSchema );
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBView::isValidField( QString strName )
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member creates the DBView in the database using the qbuCreateViewQuery.
 */

bool qbuDBView::internalCreateDBView( QString strDBViewName, QString strDBViewSQL, bool bTempView )
{
	bool retVal = ( m_pDB != nullptr) && (m_pDB->isOpen());
	if (retVal) {
		qbuCreateViewQuery viewQuery(m_pDB);
		retVal = viewQuery.create(strDBViewName,strDBViewSQL,bTempView);
		if (!retVal) {
			QString strError = QString("Failed to create the following View %1: %2 \n The database error message was %3.")
				.arg(strDBViewName)
				.arg(strDBViewSQL)
				.arg(viewQuery.lastError().text());

#ifdef QBU_DB_USES_EXCEPTIONS
			throw qbuException(__FILE__, __LINE__, qPrintable(strError), "qbuDBView::renameDBView");
#else
			databaseError(strError);
#endif //def QBU_DB_USES_EXCEPTIONS
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBView::renameDBView( QString strNewName )
{
	bool retVal = ( m_pDB != nullptr) && (m_pDB->isOpen());
	if (retVal) {
		QString strSQL;
		strSQL = QString("ALTER VIEW %1 RENAME TO %2")
			.arg(getDBViewName())
			.arg(strNewName);

		qbuSimpleQuery	query(m_pDB);

		retVal = query.exec(strSQL);
		if(retVal)
		{
			qDebug() << "DBView " << qPrintable(getDBViewName()) << " renamed to " << qPrintable(strNewName);
		}
		else
		{
			QString strError = QString("Failed to rename DBView %1 to %2. The database error message was %3.")
				.arg(getDBViewName())
				.arg(strNewName)
				.arg(query.lastError().text());

#ifdef QBU_DB_USES_EXCEPTIONS
			throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuDBView::renameDBView");
#else
			databaseError(strError);
#endif //def QBU_DB_USES_EXCEPTIONS

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBView::verifySchema()
{
	/*
	qbuDBViewSchema schema(this);
	bool retVal = schema.analyzeDBView();
	if (retVal) {

		std::auto_ptr<qbuInfo> ptr(createInfoClass());
		retVal = (ptr.get() != nullptr);
		if (retVal) {
			retVal = schema.verifyDBView(ptr.get());
		}

	}
	*/
	bool retVal = true;
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

const QStringList& qbuDBView::getFieldList() const
{
	static QStringList lst;
	return lst;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBView::dropView()
{
	bool retVal = ( m_pDB != nullptr) && (m_pDB->isOpen());
	if (retVal) {
		QString strSQL;
		strSQL = QString("DROP VIEW %1")
			.arg(getDBViewName());

		qbuSimpleQuery	query(m_pDB);

		retVal = query.exec(strSQL);
		if(retVal)
		{
			qDebug() << "View " << qPrintable(getDBViewName()) << " dropped ";
		}
		else
		{
			QString strError = QString("Failed to rename table %1. The database error message was %2.")
				.arg(getDBViewName())
				.arg(query.lastError().text());

#ifdef QBU_DB_USES_EXCEPTIONS
			throw qbuException(__FILE__,__LINE__,qPrintable(strError),"qbuDBView::dropView");
#else
			databaseError(strError);

#endif //def QBU_DB_USES_EXCEPTIONS

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBView::verifyRequiredFields(qbuInfo * pInfo, const QStringList & lstFields) const
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
		if (!retVal) {

			QString strMessage = QString("A query on table %1 will fail because the "
				"following fields are not defined in the qbuInfo class (%2): %3")
				.arg(getDBViewName())
				.arg(pInfo->metaObject()->className())
				.arg(lstMissingRequired.toCSVString());

			QLOG_WARN() << QBULOG_DATABASE_TYPE << strMessage;
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBView::viewNeedsUpdate(int nOldSchema, int nNewSchema, bool bForceUpdate)
{
    Q_UNUSED(nNewSchema);
    Q_UNUSED(nOldSchema);
    return bForceUpdate;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBView::databaseError(QString strErrorMessage)
{
	if (m_pDB) {
		m_pDB->emitDatabaseError(strErrorMessage);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
