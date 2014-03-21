#pragma once

#ifndef __TESTSETVARIABLE_H__
#define __TESTSETVARIABLE_H__

#include "qbuCmdLine/QCmd.h"

/////////////////////////////////////////////////////////////////////////////////////////

class CmdTestSetVar : public QCmd
{
public:
	CmdTestSetVar(QString strName, QString strDescription);
	virtual int Execute();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __TESTSETVARIABLE_H__

