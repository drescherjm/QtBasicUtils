#pragma once

#ifndef QCMDHELP_H
#define QCMDHELP_H

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

public:
	static QString g_strOPTBrief;

private:
	QCmdLine*	m_pCmdLine;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QCMDHELP_H
