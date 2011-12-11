#include "qbuDBSavePoint.h"
#include "qbuDatabase.h"
#include "qbuQuery.h"
#include <QUuid>
//#include "smLog.h"


/////////////////////////////////////////////////////////////////////////////////////////

qbuDBSavePoint::qbuDBSavePoint(qbuDatabase* pDB) : m_pDB(pDB), m_bSavePointStarted(false),
	m_bFailSavePoint(false)
{
	if (m_pDB != NULL) {

		m_strSavePoint = QUuid::createUuid().toString();

		m_strSavePoint.replace("{","\'");
		m_strSavePoint.replace("}","\'");

		qbuQuery query(*m_pDB);

		m_bSavePointStarted = query.exec(QString("SAVEPOINT %1;").arg(m_strSavePoint));

		if (!m_bSavePointStarted) {
			QLOG_CRIT() << "A savepoint could not be started.";
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBSavePoint::~qbuDBSavePoint()
{
	if (m_bSavePointStarted && (m_pDB != NULL)) {
		qbuQuery query(*m_pDB);

		QString strCommand;
		if (m_bFailSavePoint) {
			strCommand = "ROLLBACK TRANSACTION TO ";
		}
		else
		{
			strCommand = "RELEASE ";
		}

		bool bSuccess = query.exec(QString("%1 SAVEPOINT %2;")
			.arg(strCommand)
			.arg(m_strSavePoint));			
		if (!bSuccess) {
			if (m_bFailSavePoint) {
				QLOG_CRIT() << "A savepoint could not be rolled back";
			}
			else
			{
				QLOG_CRIT() << "A savepoint could not be released.";
			}
		
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBSavePoint::failSavePoint( bool bFail )
{
	m_bFailSavePoint = bFail;
}

