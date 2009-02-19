#include <iostream>

#include "QCmd.h"
#include "QCmdHelp.h"
#include "QCmdLine.h"
#include "QCmdParseError.h"
#include "QCmdParseException.h"
#include "QCmdHelpException.h"

using namespace QTUTILS;

/////////////////////////////////////////////////////////////////////////////////////////

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

	float fTemp = 0.0f;
	AddOpt('T',"Temperature","Temperature in Fahrenheit",fTemp);
}

int QCmdTest::Execute()
{
	quint32 nCase;
	GetArg("CaseNumber",nCase);

	std::cout << "CaseNumber=" << nCase << std::endl;

	float fTemp = 100.0f;
	GetOpt('T',fTemp);

	std::cout << "Temperature=" << fTemp << std::endl;

	return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdGo : public QCmd
{
public:
	QCmdGo(QString strName, QString strDescription);
	virtual int Execute();
};

QCmdGo::QCmdGo(QString strName, QString strDescription) :
QCmd(strName,strDescription)
{
	QStringList sl;
	sl.push_back("0");
	AddArg("CaseNumber(s)","The case number","",sl);

	float fTemp = 0.0f;
	AddOpt('T',"Temperature","Temperature in Fahrenheit",fTemp);
}

int QCmdGo::Execute()
{

	quint32 nCase;
	GetArg("CaseNumber",nCase);

	std::cout << "CaseNumber=" << nCase << std::endl;

	float fTemp = 100.0f;
	GetOpt('T',fTemp);

	std::cout << "Temperature=" << fTemp << std::endl;

	return QCmdParseError::STATUS_OK;
}


int main(int argc, char* argv[])
{

	try {
		QCmdTest	cmdTest("Test","This is the test command");
		QCmdGo		cmdGo("GO","This is the go command");

		QCmdLine myCmdLine(argc,argv);
		QCmdHelp myHelp("This command shows the help message for all commands.","");

		myCmdLine.AddCmd(&myHelp);
		myCmdLine.AddCmd(&cmdTest);
		myCmdLine.AddCmd(&cmdGo);

		myCmdLine.Parse();

		QCmd* pCmd;

		QCmdLine::iterator it = myCmdLine.begin();
		while(it != myCmdLine.end()){
			if( myCmdLine.GetNextCommand(it,pCmd) == QCmdParseError::STATUS_OK ) {
				if ( pCmd != NULL ) {
					try {
						pCmd->Parse();
						pCmd->Execute();
					}
					catch( QCmdHelpException* e) {
						std::cout << e->GetMessageString().toStdString() << std::endl;
						e->Delete();
					}
				}
			}
		}
	}
	catch( QCmdParseException* e) {
		std::cout << e->GetErrorString().toStdString() << std::endl;
		e->Delete();
	}

	return 0;
}