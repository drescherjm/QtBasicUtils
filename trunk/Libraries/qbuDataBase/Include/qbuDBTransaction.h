#ifndef __SMDBTRANSACTION_H__
#define __SMDBTRANSACTION_H__

#include "smMacros.h"

class smDatabase;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This class will simplify the handling of database transactions by freeing the user
 *  from the requirement to have to remember to commit the transaction. When this object
 *  goes out of scope the transaction is automatically committed. 
 *
 *	\ingroup smDatabase
 *
 */

class smDBTransaction 
{
public:
	smDBTransaction(smDatabase * pDB);
	virtual ~smDBTransaction();
public:
	void			failTransaction(bool bFail);
private:
	smDatabase*		m_pDB;
	bool			m_bTransactionStarted;
	bool			m_bFailTransaction;
private:
	// The following are intentionally not implemented to prevent copying this object.
	smDBTransaction& operator=(const smDBTransaction & noAssign );
	smDBTransaction(const smDBTransaction & noCopy );
	smDBTransaction();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMDBTRANSACTION_H__
