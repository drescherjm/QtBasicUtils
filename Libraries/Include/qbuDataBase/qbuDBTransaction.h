#pragma once

#ifndef QBUDBTRANSACTION_H
#define QBUDBTRANSACTION_H

class qbuDatabase;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	This class will simplify the handling of database transactions by freeing the user
 *  from the requirement to have to remember to commit the transaction. When this object
 *  goes out of scope the transaction is automatically committed. 
 *
 *	\ingroup qbuDatabase
 *
 */

class qbuDBTransaction 
{
public:
	qbuDBTransaction(std::shared_ptr<qbuDatabase> pDB);
	virtual ~qbuDBTransaction();
public:
	void			failTransaction(bool bFail);
private:
	std::shared_ptr<qbuDatabase>	m_pDB;
	bool			m_bTransactionStarted;
	bool			m_bFailTransaction;
private:
	bool			criticalCanNotCommit();
	bool			warningCanNotCommit();
	// The following are intentionally not implemented to prevent copying this object.
	qbuDBTransaction& operator=(const qbuDBTransaction & noAssign );
	qbuDBTransaction(const qbuDBTransaction & noCopy );
	qbuDBTransaction();

protected:
	virtual	void	databaseError(QString strErrorMessage);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBTRANSACTION_H

