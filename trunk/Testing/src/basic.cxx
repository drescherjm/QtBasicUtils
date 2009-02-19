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

	int nSum = 0;
	QStringList::iterator it;
	for(it = sl.begin(); it != sl.end();++it) {
		nSum += it->toInt();
	}

	AddOpt('S',"The sum","This is the expected sum of Integer(s)",nSum);
}

int QCmdStringListArg::Execute()
{

	QStringList sl;
	GetArg("Integer(s)",sl);

	int nSum = 0;
	QStringList::iterator it;
	for(it = sl.begin(); it != sl.end();++it) {
		std::cout << "Integer(s)=" << it->toStdString() << std::endl;
		nSum += it->toInt();
	}

	int nExpectedSum = 0;
	GetOpt('S',nExpectedSum);

	std::cout << "Expected Sum=" << nExpectedSum << std::endl;
	std::cout << "Actual Sum=" << nSum << std::endl;

	return (nExpectedSum == nSum) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdStringListOpt : public QCmd
{
public:
	QCmdStringListOpt(QString strName, QString strDescription);
	virtual int Execute();
};

QCmdStringListOpt::QCmdStringListOpt(QString strName, QString strDescription) :
QCmd(strName,strDescription)
{
	QStringList sl;
	sl.push_back("0");
	sl.push_back("1");
	sl.push_back("2");
	AddOpt('I',"The integers to sum","",sl);

	int nSum = 0;
	QStringList::iterator it;
	for(it = sl.begin(); it != sl.end();++it) {
		nSum += it->toInt();
	}

	AddOpt('S',"The sum","This is the expected sum of Integer(s)",nSum);
}

int QCmdStringListOpt::Execute()
{

	QStringList sl;
	GetOpt('I',sl);

	int nSum = 0;
	QStringList::iterator it;
	for(it = sl.begin(); it != sl.end();++it) {
		std::cout << "Integer(s)=" << it->toStdString() << std::endl;
		nSum += it->toInt();
	}

	int nExpectedSum = 0;
	GetOpt('S',nExpectedSum);

	std::cout << "Expected Sum=" << nExpectedSum << std::endl;
	std::cout << "Actual Sum=" << nSum << std::endl;

	return (nExpectedSum == nSum) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	
	int retVal =0;


	try {
		QCmdTest			cmdTest("Test","This is the test command");
		QCmdStringListArg	cmdStrLstArg("STRLSTARG","This tests the string list as an argument.");
		QCmdStringListOpt	cmdStrLstOpt("STRLSTOPT","This tests the string list as an option.");

		QCmdLine myCmdLine(argc,argv);
		QCmdHelp myHelp("This command shows the help message for all commands.","");

		myCmdLine.AddCmd(&cmdTest);
		myCmdLine.AddCmd(&cmdStrLstArg);
		myCmdLine.AddCmd(&cmdStrLstOpt);
		myCmdLine.AddCmd(&myHelp);


		myCmdLine.Parse();

		QCmd* pCmd;

		QCmdLine::iterator it = myCmdLine.begin();
		while(it != myCmdLine.end()){
			try {
				retVal = myCmdLine.GetNextCommand(it,pCmd);
				if( retVal == QCmdParseError::STATUS_OK ) {
					if ( pCmd != NULL ) {
						try {
							pCmd->Parse();
							retVal = pCmd->Execute();
						}
						catch( QCmdHelpException* e) {
							std::cout << e->GetMessageString().toStdString() << std::endl;
							e->Delete();
						}
					}
				}
				else
				{
					std::cout << QCmdParseError::GetErrorString(retVal).toStdString() << std::endl;
				}
				if (retVal == QCmdParseError::STATUS_OK) {
					std::cout << "SUCCEEDED" << std::endl;
				}
				else{
					std::cout << "FAILED" << std::endl;
				}
			}
			catch( QCmdParseException* e) {
				std::cout << e->GetErrorString().toStdString() << std::endl;
				e->Delete();

				retVal = -1;

				std::cout << "FAILED" << std::endl;
			}
		}
	}
	catch( QCmdParseException* e) {
		std::cout << e->GetErrorString().toStdString() << std::endl;
		e->Delete();

		retVal = -1;

		std::cout << "FAILED" << std::endl;
	}

	int c;
	std::cin >> c;

	return retVal;
}
