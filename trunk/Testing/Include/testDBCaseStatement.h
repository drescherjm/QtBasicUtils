#include "qbuCmdLine/QCmd.h"

/////////////////////////////////////////////////////////////////////////////////////////

class CmdTestDBCaseStatement : public QCmd
{
public:
	CmdTestDBCaseStatement(QString strName, QString strDescription);
	virtual int Execute();

private:
	bool	test0();
	void	displayComparisonMessageIfFalse(bool retVal, 
		const QString strExpected, const QString strVal);
};

/////////////////////////////////////////////////////////////////////////////////////////

