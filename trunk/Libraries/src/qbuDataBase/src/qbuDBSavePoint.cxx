#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDBSavePoint.h"
#include "qbuDataBase/qbuDatabase.h"
#include "qbuDataBase/qbuQuery.h"
#include "qbuLog/qbuLog.h"

#include <QUuid>
#include <QThread>
#include <QCoreApplication>
#include <QMessageBox>

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBSavePoint::qbuDBSavePoint(std::shared_ptr<qbuDatabase> pDB, bool bStart, QString strBaseName) : m_pDB(pDB), m_bSavePointStarted(false),
m_bFailSavePoint(false)
{
	if (m_pDB != nullptr) {

		m_strSavePoint = strBaseName + QUuid::createUuid().toString();

		m_strSavePoint.remove("{").remove("}");

		m_strSavePoint.prepend("\'");
		m_strSavePoint.append("\'");

		if (bStart) {
			startSavePoint();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBSavePoint::~qbuDBSavePoint()
{
	if (m_bSavePointStarted && (m_pDB != nullptr)) {
		bool bSuccess;

		qbuQuery query(m_pDB);

		QString strCommand;
		if (m_bFailSavePoint) {
			bSuccess = rollbackSavePoint(query);
		}
		else
		{
			bSuccess = releaseSavePoint(query);
		}

		if (!bSuccess) {
			if (m_bFailSavePoint) {
				QString strMsg = QString("A SAVEPOINT could not be rolled back. The following error occurred: %1").arg(query.lastError().text());
				QLOG_CRIT() << QBULOG_DATABASE_TYPE << strMsg;

			}
			else
			{

				QString strMsg = QString("A SAVEPOINT could not be released. Was nothing written to the database between savepoints? "
					"Note this will frequently happen when the logout button was pressed in review mode. "
					"The following error occurred: %1").arg(query.lastError().text());
				QLOG_CRIT() << QBULOG_DATABASE_TYPE << strMsg;
				bSuccess = criticalCanNotRelease(query);
				if (!bSuccess) {

#ifdef QBU_HAVE_EXCEPTIONS
					throw smException(__FILE__, __LINE__, qPrintable(strMsg), "qbuDBSavePoint::~qbuDBSavePoint");
#else
					qDebug() << qPrintable(strError);
#endif //def QBU_HAVE_EXCEPTIONS

				}
			}

		}
		else
		{
			if (m_bFailSavePoint) {

				// A rolled back SAVEPOINT will still be on the transaction stack. This should remove it. 
				bSuccess = releaseSavePoint(query);

				QString strMsg = QString("The following SAVEPOINT was rolled back: %1").arg(m_strSavePoint);
				QLOG_INFO() << QBULOG_DATABASE_TYPE << strMsg;
			}
			else
			{
				QString strMsg = QString("The following SAVEPOINT was released: %1").arg(m_strSavePoint);
				QLOG_INFO() << QBULOG_DATABASE_TYPE << strMsg;
			}

		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBSavePoint::failSavePoint(bool bFail)
{
	m_bFailSavePoint = bFail;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSavePoint::isStarted()
{
	return m_bSavePointStarted;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSavePoint::startSavePoint()
{
	bool retVal = isStarted();
	if (!retVal) {
		qbuQuery query(m_pDB);

		m_bSavePointStarted = query.exec(QString("SAVEPOINT %1;").arg(m_strSavePoint));

		if (!m_bSavePointStarted) {
			QString strMsg = QString("A SAVEPOINT could not be started. The following error occurred: %1").arg(m_pDB->lastError().text());
			QLOG_CRIT() << QBULOG_DATABASE_TYPE << strMsg;

#ifdef QBU_HAVE_EXCEPTIONS
			throw smException(__FILE__, __LINE__, qPrintable(strMsg), "qbuDBSavePoint::startSavePoint");
#else
			qDebug() << qPrintable(strError);
#endif //def QBU_HAVE_EXCEPTIONS

		}
		else
		{
			QString strMsg = QString("The following SAVEPOINT was started: %1").arg(m_strSavePoint);
			QLOG_INFO() << QBULOG_DATABASE_TYPE << strMsg;
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSavePoint::criticalCanNotRelease(qbuQuery & query)
{
	bool retVal;

	QString strLastError = query.lastError().text();

	// Ignore programming errors like "no such savepoint"
	retVal = strLastError.contains("such", Qt::CaseInsensitive);

	if (!retVal) {
		if (QThread::currentThreadId() == QCoreApplication::instance()->thread()->currentThreadId()) {

			int reply = QMessageBox::critical(nullptr, "Database Locked",
				"The database is locked because another program has it open. <br> "
				"<b>Please STOP here and have John Drescher or Durwin Logue fix this.</b>"
				"<br>Results will not be recorded until this is fixed.",
				QMessageBox::Retry | QMessageBox::Abort);
			if (reply == QMessageBox::Retry){
				retVal = releaseSavePoint(query);

				if (!retVal) {
					retVal = criticalCanNotRelease(query);
				}
			}
			else {
				retVal = warningCanNotRelease(query);
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSavePoint::warningCanNotRelease(qbuQuery & query)
{
	bool retVal;
	int reply = QMessageBox::warning(nullptr, "Database Locked (second chance)",
		"The database is locked because another program has it open. <br> "
		"<br><b>Note: Results will be lost if you click Abort</b>",
		QMessageBox::Retry | QMessageBox::Abort);

	if (reply == QMessageBox::Retry) {
		retVal = releaseSavePoint(query);
		if (!retVal) {
			retVal = criticalCanNotRelease(query);
		}
	}
	else
	{
		retVal = false;
	}

	return retVal;

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSavePoint::releaseSavePoint(qbuQuery & query)
{
	bool retVal = query.exec(QString("RELEASE SAVEPOINT %1;").arg(m_strSavePoint));
	if (!retVal) {
		QLOG_CRIT() << QBULOG_DATABASE_TYPE << query.lastError().text();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBSavePoint::rollbackSavePoint(qbuQuery & query)
{
	bool retVal = query.exec(QString("ROLLBACK TRANSACTION TO SAVEPOINT %1;").arg(m_strSavePoint));
	if (!retVal) {
		QLOG_CRIT() << QBULOG_DATABASE_TYPE << query.lastError().text();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

