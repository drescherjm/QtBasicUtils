#include <iostream>

#include "QCmd.h"
#include "QCmdParseError.h"

using namespace QTUTILS;

class QCmdTest : public QCmd
{
public:
	QCmdTest(QString strName, QString strDescription);
	virtual int Execute();
};

QCmdTest::QCmdTest(QString strName, QString strDescription) :
QCmd(strName,strDescription)
{
	AddArg("CaseNumber","The case number","",(quint32)0);
}

int QCmdTest::Execute()
{
	quint32 nCase;
	GetArg("CaseNumber",nCase);
	return QCmdParseError::STATUS_OK;
}

int main()
{
	QCmdTest cmdTest("Test","This is the test command");

	cmdTest.Execute();

	return 0;
}