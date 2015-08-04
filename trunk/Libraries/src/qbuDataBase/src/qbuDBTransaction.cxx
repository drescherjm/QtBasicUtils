#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDBTransaction.h"
#include "qbuDataBase/qbuDatabase.h"
#include "qbuLog/qbuLog.h"
#include <QMessageBox>
#include <QThread>
#include <QCoreApplication>

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBTransaction::qbuDBTransaction(std::shared_ptr<qbuDatabase> pDB) : m_pDB(pDB), m_bTransactionStarted(false),
	m_bFailTransaction(false)
{
	if (m_pDB != nullptr) {
		m_bTransactionStarted = m_pDB->transaction();
		if (!m_bTransactionStarted) {
			QString strError = QString("Could not start a transaction: %1").arg(m_pDB->lastError().text());
			QLOG_CRIT() << QBULOG_DATABASE_TYPE << strError;

#ifdef QBU_HAVE_EXCEPTIONS
			throw qbuException(__FILE__, __LINE__, qPrintable(strError), "qbuDBTransaction::qbuDBTransaction");
#else
			qDebug() << qPrintable(strError);
#endif //def QBU_HAVE_EXCEPTIONS

		}
		else
		{
			QLOG_DATABASE() << "BEGIN TRANSACTION";
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBTransaction::~qbuDBTransaction()
{
	if (m_bTransactionStarted && (m_pDB != nullptr)) {
		if (!m_bFailTransaction) {
			bool bSuccess = m_pDB->commit();
			if (!bSuccess) {

				QString strMsg = QString("A commit failed with the following error: %1").arg(m_pDB->lastError().text());

				QLOG_CRIT() << QBULOG_DATABASE_TYPE << strMsg;

				// Lets attempt recovery..
				if (m_pDB->lastError().text().contains("lock",Qt::CaseInsensitive)) {

					// Check if the current thread is the same as the GUI Thread
					if (QThread::currentThreadId() == QCoreApplication::instance()->thread()->currentThreadId()) {

						bSuccess = criticalCanNotCommit();
					}

				}

				if (!bSuccess) {

					m_pDB->rollback();

#ifdef QBU_HAVE_EXCEPTIONS
					throw qbuException(__FILE__, __LINE__, qPrintable(strMsg), "qbuDBTransaction::~qbuDBTransaction");
#else
					qDebug() << qPrintable(strError);
#endif //def SM_HAVE_EXCEPTIONS

				}
			}
			else
			{
				QLOG_DATABASE() << "END TRANSACTION: COMMIT";
			}

		}
		else
		{
			if (!m_pDB->rollback()) {


				QString strMsg = QString("A commit could not be rolled back as a result of the following database error: %1").arg(m_pDB->lastError().text());

				QLOG_CRIT() << QBULOG_DATABASE_TYPE << strMsg;

#ifdef QBU_HAVE_EXCEPTIONS
				throw qbuException(__FILE__, __LINE__, qPrintable(strMsg), "qbuDBTransaction::~qbuDBTransaction");
#else
				qDebug() << qPrintable(strError);
#endif //def SM_HAVE_EXCEPTIONS

			}
			else
			{
				QLOG_DATABASE() << "END TRANSACTION: ROLLBACK";
			}
		}
		
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBTransaction::failTransaction( bool bFail )
{
	m_bFailTransaction = bFail;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBTransaction::criticalCanNotCommit()
{
	bool retVal;

	int reply = QMessageBox::critical(nullptr, "Database Locked",
		"The database is locked because another program has it open. <br> "
		"<b>Please STOP here and have John Drescher or Durwin Logue fix this.</b>"
		"<br>Results will not be recorded until this is fixed.",
		QMessageBox::Retry | QMessageBox::Abort);
	if(reply==QMessageBox::Retry){
		retVal = m_pDB->commit();

		if (!retVal) {
			retVal = criticalCanNotCommit();
		}
	}
	else {
		retVal = warningCanNotCommit();
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuDBTransaction::warningCanNotCommit()
{
	bool retVal;
	int reply = QMessageBox::warning(nullptr, "Database Locked (second chance)",
		"The database is locked because another program has it open. <br> "
		"<br><b>Note: Results will be lost if you click Abort</b>",
		QMessageBox::Retry | QMessageBox::Abort);

	if (reply == QMessageBox::Retry) {
		retVal = m_pDB->commit();
		if (!retVal) {
			retVal = criticalCanNotCommit();
		}
	}
	else
	{
		retVal = false;
	}

	return retVal;

}

/////////////////////////////////////////////////////////////////////////////////////////
