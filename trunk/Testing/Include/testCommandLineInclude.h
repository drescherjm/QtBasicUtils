#include "qbuCmdLine/QCmd.h"



/////////////////////////////////////////////////////////////////////////////////////////

class QCmdTestCmdLineFileInclude : public QCmd
{
public:
	QCmdTestCmdLineFileInclude(QString strName, QString strDescription);
	virtual int Execute();
private:
	bool	writeTestFile(QString strFileName, QString strMsg);
	int		runTest(int nTest);
	int		runTest_DoubleQuotes_1();
public:
	enum Tests{
		ALL_TESTS=0,
		DOUBLE_QUOTES_1=1,
		NUM_TESTS,
	};
};

/////////////////////////////////////////////////////////////////////////////////////////


