//#ifdef _MSC_VER
#include "smDBBasePCH.h"
//#endif //def _MSC_VER

#include "smDBTransaction.h"
#include "smDatabase.h"


/////////////////////////////////////////////////////////////////////////////////////////

smDBTransaction::smDBTransaction(smDatabase* pDB) : m_pDB(pDB), m_bTransactionStarted(false),
	m_bFailTransaction(false)
{
	if (m_pDB != NULL) {
		m_bTransactionStarted = m_pDB->transaction();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

smDBTransaction::~smDBTransaction()
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

void smDBTransaction::failTransaction( bool bFail )
{
	m_bFailTransaction = bFail;
}

