#pragma once

#ifndef QBUDBSAVEPOINT_H
#define QBUDBSAVEPOINT_H

#include <QString>

class qbuDatabase;

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
	qbuDBSavePoint(qbuDatabase * pDB);
	virtual ~qbuDBSavePoint();
public:
	void			failSavePoint(bool bFail);
private:
	qbuDatabase*		m_pDB;
	bool			m_bSavePointStarted;
	bool			m_bFailSavePoint;
	QString			m_strSavePoint;
private:
	// The following are intentionally not implemented to prevent copying this object.
	qbuDBSavePoint& operator=(const qbuDBSavePoint & noAssign );
	qbuDBSavePoint(const qbuDBSavePoint & noCopy );
	qbuDBSavePoint();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUDBSAVEPOINT_H
