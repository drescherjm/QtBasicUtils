#include "qbuDataBasePCH.h"

#include "qbuDataBase/qbuDBTransaction.h"
#include "qbuDataBase/qbuDatabase.h"

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBTransaction::qbuDBTransaction(qbuDatabase* pDB) : m_pDB(pDB), m_bTransactionStarted(false),
	m_bFailTransaction(false)
{
	if (m_pDB != NULL) {
		m_bTransactionStarted = m_pDB->transaction();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuDBTransaction::~qbuDBTransaction()
{
	if (m_bTransactionStarted && (m_pDB != NULL)) {
		if (!m_bFailTransaction) {
			m_pDB->commit();
		}
		else
		{
			m_pDB->rollback();
		}
		
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuDBTransaction::failTransaction( bool bFail )
{
	m_bFailTransaction = bFail;
}

