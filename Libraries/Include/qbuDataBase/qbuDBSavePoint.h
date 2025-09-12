#pragma once

#ifndef QBUDBSAVEPOINT_H
#define QBUDBSAVEPOINT_H

#include <QString>
#include <memory>

class qbuDatabase;
class qbuQuery;

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This class will simplify the handling of database SavePoints by freeing the user
 *  from the requirement to have to remember to release the SavePoints.
 *
 *	\note
 *	- When this object goes out of scope the SavePoints is automatically released. 
 *	- Unlike transactions SAVEPOINTS can be nested.
 *
 *	\ingroup qbuDatabase
 *
 *	\see qbuDBTransaction
 */

class qbuDBSavePoint
{
public:
	qbuDBSavePoint(std::shared_ptr<qbuDatabase> pDB, bool bStart = true, QString strBaseName = QString());
	virtual ~qbuDBSavePoint();
public:
	void			failSavePoint(bool bFail);
	bool			startSavePoint();
	bool			isStarted();
private:
	std::shared_ptr<qbuDatabase>		m_pDB;
	bool			m_bSavePointStarted;
	bool			m_bFailSavePoint;
	QString			m_strSavePoint;
private:
	// The following are intentionally not implemented to prevent copying this object.
	qbuDBSavePoint& operator=(const qbuDBSavePoint & noAssign);
	qbuDBSavePoint(const qbuDBSavePoint & noCopy);
	qbuDBSavePoint();
private:
	bool	warningCanNotRelease(qbuQuery & query);
	bool	criticalCanNotRelease(qbuQuery & query);
	bool	releaseSavePoint(qbuQuery & query);
	bool	rollbackSavePoint(qbuQuery & query);

protected:
	virtual	void	databaseError(QString strErrorMessage);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBSAVEPOINT_H
