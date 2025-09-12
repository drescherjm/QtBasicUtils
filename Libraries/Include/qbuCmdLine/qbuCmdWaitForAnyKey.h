#pragma once

#ifndef QBUCMDWAITFORANYKEY_H
#define QBUCMDWAITFORANYKEY_H

#include "qbuCmdLine/QCmd.h"
#include "qbuBase/qbuMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuCmdWaitForAnyKey : public QCmd
{
	QBU_DECLARE_SUPERCLASS(QCmd);
public:
	qbuCmdWaitForAnyKey(QString strName="PAUSE", 
		QString strDescription="This command will wait for a keystroke.");

	virtual int Execute();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUCMDWAITFORANYKEY_H
