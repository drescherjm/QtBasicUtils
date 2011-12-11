#ifndef __SMDBSAVEPOINT_H__
#define __SMDBSAVEPOINT_H__

#include "smMacros.h"

class smDatabase;

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
 *	\ingroup smDatabase
 *
 *	\see smDBTransaction
 */

class smDBSavePoint 
{
public:
	smDBSavePoint(smDatabase * pDB);
	virtual ~smDBSavePoint();
public:
	void			failSavePoint(bool bFail);
private:
	smDatabase*		m_pDB;
	bool			m_bSavePointStarted;
	bool			m_bFailSavePoint;
	QString			m_strSavePoint;
private:
	// The following are intentionally not implemented to prevent copying this object.
	smDBSavePoint& operator=(const smDBSavePoint & noAssign );
	smDBSavePoint(const smDBSavePoint & noCopy );
	smDBSavePoint();
};

/////////////////////////////////////////////////////////////////////////////////////////


#endif //__SMDBSAVEPOINT_H__