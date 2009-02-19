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

class QCmdStringListArg : public QCmd
{
public:
	QCmdStringListArg(QString strName, QString strDescription);
	virtual int Execute();
};

QCmdStringListArg::QCmdStringListArg(QString strName, QString strDescription) :
QCmd(strName,strDescription)
{
	QStringList sl;
	sl.push_back("0");
	sl.push_back("1");
	sl.push_back("2");
	AddArg("Integer(s)","The integers to sum","",sl);

	int nSum;
	QStringList::iterator it;
	for(it = sl.begin(); it != sl.end();++it) {
		std::cout << "Integer(s)=" << it->toStdString() << std::endl;
	}

	AddOpt('S',"The sum to test","Temperature in Fahrenheit",fTemp);
}

int QCmdStringListArg::Execute()
{

	QStringList sl;
	GetArg("CaseNumber(s)",sl);

	QStringList::iterator it;
	for(it = sl.begin(); it != sl.end();++it) {
		std::cout << "CaseNumber(s)=" << it->toStdString() << std::endl;
	}

	float fTemp = 100.0f;
	GetOpt('T',fTemp);

	std::cout << "Temperature=" << fTemp << std::endl;

	return QCmdParseError::STATUS_OK;
}


int main(int argc, char* argv[])
{
	
	int retVal =0;


	try {
		QCmdTest			cmdTest("Test","This is the test command");
		QCmdStringListArg	cmdStrLst("STRLST","This tests the string list as an argument.");

		QCmdLine myCmdLine(argc,argv);
		QCmdHelp myHelp("This command shows the help message for all commands.","");

		myCmdLine.AddCmd(&myHelp);
		myCmdLine.AddCmd(&cmdTest);
		myCmdLine.AddCmd(&cmdStrLst);

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

		retVal = -1;
	}


	int c;
	std::cin >> c;

	return retVal;
}
