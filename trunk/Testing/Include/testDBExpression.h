#pragma once

#ifndef TESTDBEXPRESSION_H
#define TESTDBEXPRESSION_H

#include "qbuCmdLine/QCmd.h"

/////////////////////////////////////////////////////////////////////////////////////////

class CmdTestDBExpression : public QCmd
{
public:
	CmdTestDBExpression(QString strName, QString strDescription);
	virtual int Execute();

private:
	bool	test0();
	void	displayComparisonMessageIfFalse(bool retVal, 
		const QString strExpected, const QString strVal);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // TESTDBEXPRESSION_H
