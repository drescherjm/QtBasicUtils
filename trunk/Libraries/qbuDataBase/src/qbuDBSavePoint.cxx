//#ifdef _MSC_VER
#include "smDBBasePCH.h"
//#endif //def _MSC_VER

#include "smDBSavePoint.h"
#include "smDatabase.h"
#include "smQuery.h"
#include <QUuid>
#include "smLog.h"


/////////////////////////////////////////////////////////////////////////////////////////

smDBSavePoint::smDBSavePoint(smDatabase* pDB) : m_pDB(pDB), m_bSavePointStarted(false),
	m_bFailSavePoint(false)
{
	if (m_pDB != NULL) {

		m_strSavePoint = QUuid::createUuid().toString();

		m_strSavePoint.replace("{","\'");
		m_strSavePoint.replace("}","\'");

		smQuery query(*m_pDB);

		m_bSavePointStarted = query.exec(QString("SAVEPOINT %1;").arg(m_strSavePoint));

		if (!m_bSavePointStarted) {
			QLOG_CRIT() << "A savepoint could not be started.";
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBSavePoint::~smDBSavePoint()
{
	if (m_bSavePointStarted && (m_pDB != NULL)) {
		smQuery query(*m_pDB);

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

void smDBSavePoint::failSavePoint( bool bFail )
{
	m_bFailSavePoint = bFail;
}

