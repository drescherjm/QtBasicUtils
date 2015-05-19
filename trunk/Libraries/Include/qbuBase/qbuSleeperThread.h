#pragma once

#ifndef QBUSLEEPERTHREAD_H
#define QBUSLEEPERTHREAD_H

#include <QThread>

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief 
 *	This class exposes the protected msleep function from QThread as public so it 
 *	can be used outside a QThread. 
 *
 *	\sa http://stackoverflow.com/questions/1950160/what-can-i-use-to-replace-sleep-and-usleep-in-my-qt-app
 */

/////////////////////////////////////////////////////////////////////////////////////////

class qbuSleeperThread : public QThread
{
public:
	static void msleep(unsigned long msecs)
	{
		QThread::msleep(msecs);
	}
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUSLEEPERTHREAD_H
