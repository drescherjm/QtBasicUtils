#pragma once

#ifndef __QCMDHELP_H__
#define __QCMDHELP_H__


#include "qbuCmdLine/QCmd.h"
#include "qbuCmdLine/QCmdLine.h"

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdHelp : public QCmd
{
	friend class QCmdLine;
public:
	QCmdHelp(QString strDescription, QString strExplanation);
	virtual int Execute();
protected:
	QCmdLine*	GetCmdLine();
private:
	QCmdLine*	m_pCmdLine;
};


/////////////////////////////////////////////////////////////////////////////////////////

#endif // __QCMDHELP_H__

