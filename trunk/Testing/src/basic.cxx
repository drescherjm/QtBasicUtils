#include <iostream>

#include "QCmd.h"
#include "QCmdHelp.h"
#include "QCmdLine.h"
#include "QCmdParseError.h"
#include "QCmdParseException.h"
#include "QCmdHelpException.h"
#include "testxml.h"
#include "testUserProps.h"
#include <QMessageBox>
#include <QApplication>
#include <QTimer>

#include <math.h>

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

	float fTemp = 32.0f;
	AddOpt("T","Temperature","Temperature in Fahrenheit",fTemp);
}

int QCmdTest::Execute()
{
	quint32 nCase;
	GetArg("CaseNumber",nCase);

	std::cout << "CaseNumber=" << nCase << std::endl;

	float fTemp = 100.0f;
	GetOpt("T",fTemp);

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

	AddOpt("S","The sum","This is the expected sum of Integer(s)",nSum);
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
	GetOpt("S",nExpectedSum);

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
	AddOpt("I","The integers to sum","",sl);

	int nSum = 0;
	QStringList::iterator it;
	for(it = sl.begin(); it != sl.end();++it) {
		nSum += it->toInt();
	}

	AddOpt("S","The sum","This is the expected sum of Integer(s)",nSum);
}

int QCmdStringListOpt::Execute()
{

	QStringList sl;
	GetOpt("I",sl);

	int nSum = 0;
	QStringList::iterator it;
	for(it = sl.begin(); it != sl.end();++it) {
		std::cout << "Integer(s)=" << it->toStdString() << std::endl;
		nSum += it->toInt();
	}

	int nExpectedSum = 0;
	GetOpt("S",nExpectedSum);

	std::cout << "Expected Sum=" << nExpectedSum << std::endl;
	std::cout << "Actual Sum=" << nSum << std::endl;

	QString str = exportCommandString('+');

	return (nExpectedSum == nSum) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////

#define NUM_FLOAT_ARGS 5

class QCmdFloatArgs : public QCmd
{
public:
	QCmdFloatArgs(QString strName, QString strDescription);
	virtual int Execute();
};

QCmdFloatArgs::QCmdFloatArgs(QString strName, QString strDescription) :
QCmd(strName,strDescription)
{
	float fVal = 1.0f;
	AddArg("F0","This is a required float value","",fVal);
	EndRequiredArguments();

	float fSum = fVal;
	for(int i=1; i < NUM_FLOAT_ARGS;++i) {
		QString str;
		str = QString("F%1").arg(i);

		AddArg(str,"This is an optional float value","",fVal);
		fSum += fVal;
	}
		
	AddOpt("S","This is the sum of the required and optional float values","",fSum);
}

int QCmdFloatArgs::Execute()
{
	float fSum = 0.0;
	for(int i=0; i < NUM_FLOAT_ARGS;++i) {
		float fVal = 0.0;
		QString str;
		str = QString("F%1").arg(i);
		GetArg(str,fVal);
		fSum += fVal;
	}

	float fExpectedSum = 0.0;
	GetOpt("S",fExpectedSum);

	std::cout << "Expected Sum=" << fExpectedSum << std::endl;
	std::cout << "Actual Sum=" << fSum << std::endl;

	bool bTest = (fabs(fExpectedSum-fSum) < 0.001);

	return (bTest) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////

#define NUM_DOUBLE_ARGS 5

class QCmdDoubleArgs : public QCmd
{
public:
	QCmdDoubleArgs(QString strName, QString strDescription);
	virtual int Execute();
};

QCmdDoubleArgs::QCmdDoubleArgs(QString strName, QString strDescription) :
QCmd(strName,strDescription)
{
	double fVal = 1.0f;
	AddArg("D0","This is a required double value","",fVal);
	EndRequiredArguments();

	double fSum = fVal;
	for(int i=1; i < NUM_DOUBLE_ARGS;++i) {
		QString str;
		str = QString("D%1").arg(i);
		AddArg(str,"This is an optional double value","",fVal);
		fSum += fVal;
	}

	AddOpt("S","This is the sum of the required and optional double values","",fSum);
}

int QCmdDoubleArgs::Execute()
{
	double fSum = 0.0;
	for(int i=0; i < NUM_DOUBLE_ARGS;++i) {
		double fVal = 0.0;
		QString str;
		str = QString("D%1").arg(i);
		GetArg(str,fVal);
		fSum += fVal;
	}

	double fExpectedSum = 0.0;
	GetOpt("S",fExpectedSum);

	std::cout << "Expected Sum=" << fExpectedSum << std::endl;
	std::cout << "Actual Sum=" << fSum << std::endl;

	bool bTest = (fabs(fExpectedSum-fSum) < 0.001);

	return (bTest) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdEnter : public QCmd
{
public:
	QCmdEnter(QString strName, QString strDescription);
	virtual int Execute();
};

QCmdEnter::QCmdEnter(QString strName, QString strDescription) :
QCmd(strName,strDescription)
{
	
}

int QCmdEnter::Execute()
{
	
	std::cout << "Press a key then enter to continue!" << std::endl;

	int c;
	std::cin >> c;

	return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdOptBoolTest : public QCmd
{
public:
	QCmdOptBoolTest(QString strName, QString strDescription);
	virtual int Execute();
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptBoolTest::QCmdOptBoolTest( QString strName, QString strDescription ) :
	QCmd(strName,strDescription)
{
	bool bTest = true;
	AddOpt("B","Test command","",bTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdOptBoolTest::Execute()
{	
	int retVal;
	bool bTest;
	retVal = GetOpt("B",bTest);
	if (retVal == QCmdParseError::STATUS_OK) {
		retVal = (bTest == true) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
		if (retVal == QCmdParseError::STATUS_OK) {
			bool bVal = false;
			retVal = SetOpt("B",bVal);
			if (wasSuccessful(retVal)) {
				retVal = GetOpt("B",bTest);
				if (wasSuccessful(retVal)) {
						retVal = (bTest == false) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
				}
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdOptExtBoolTest : public QCmd
{
public:
	QCmdOptExtBoolTest(QString strName, QString strDescription);
	virtual int Execute();
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptExtBoolTest::QCmdOptExtBoolTest( QString strName, QString strDescription ) :
QCmd(strName,strDescription)
{
	bool bTest = true;
	AddOpt("use_extended","Extended bool test","",bTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdOptExtBoolTest::Execute()
{	
	int retVal;
	bool bTest;
	retVal = GetOpt("use_extended",bTest);
	if (retVal == QCmdParseError::STATUS_OK) {
		retVal = (bTest == true) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
		if (retVal == QCmdParseError::STATUS_OK) {
			bool bVal = false;
			retVal = SetOpt("use_extended",bVal);
			if (wasSuccessful(retVal)) {
				retVal = GetOpt("use_extended",bTest);
				if (wasSuccessful(retVal)) {
					retVal = (bTest == false) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
				}
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdExtOpt : public QCmd
{
public:
	QCmdExtOpt(QString strName, QString strDescription);
	virtual int Execute();
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdExtOpt::QCmdExtOpt( QString strName, QString strDescription ) :
QCmd(strName,strDescription)
{
	int nVal = 1;
	AddOpt("V0","First Value","",nVal);
	AddOpt("V1","Second Value","",nVal);
	AddOpt("S","Sum","",nVal+nVal);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdExtOpt::Execute()
{	
	int retVal;
	int nVal0	=1;
	int nVal1	=0;
	int nSum	=-1;
	retVal = GetOpt("V0",nVal0);
	if (retVal == QCmdParseError::STATUS_OK) {
		retVal = GetOpt("V1",nVal1);
		if (retVal == QCmdParseError::STATUS_OK) {
			retVal = GetOpt("S",nSum);
			if (retVal == QCmdParseError::STATUS_OK) {
				retVal = (nVal0 + nVal1) == nSum ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
			}
		}
	}
	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	
	int retVal =0;

	QApplication app(argc, argv);

	try {
		QCmdEnter			cmdEnter("PAUSE","Use this to require user to press enter to exit." );
		QCmdTest			cmdTest("Test","This is the test command");
		QCmdStringListArg	cmdStrLstArg("STRLSTARG","This tests the string list as an argument.");
		QCmdStringListOpt	cmdStrLstOpt("STRLSTOPT","This tests the string list as an option.");
		QCmdOptBoolTest		cmdBoolOpt("BOOLOPT","This tests the bool an option.");
		QCmdOptExtBoolTest	cmdExtBoolOpt("EXTBOOLOPT","This tests the bool an extended option.");
		QCmdExtOpt			cmdExtOpt("EXTOPT","This tests the extended options.");

		QCmdFloatArgs		cmdFloatArgs("FLOATARGS","This tests float as an arguments.");
		QCmdDoubleArgs		cmdDoubleArgs("DOUBLEARGS","This tests double as an arguments.");
		QCmdTestXMLExport	cmdTestXMLEXP("XMLEXP","This tests various exports of xml on the Property class.");
		QCmdTestUserProps	cmdTestUserProps("USERPROP","This tests various exports of examples of using UserProps with the Property class.");


		QCmdLine myCmdLine(argc,argv);
		QCmdHelp myHelp("This command shows the help message for all commands.","");

		myCmdLine.AddCmd(&cmdEnter);
		myCmdLine.AddCmd(&cmdTest);
		myCmdLine.AddCmd(&cmdStrLstArg);
		myCmdLine.AddCmd(&cmdStrLstOpt);
		myCmdLine.AddCmd(&cmdBoolOpt);
		myCmdLine.AddCmd(&cmdExtBoolOpt);
		myCmdLine.AddCmd(&cmdExtOpt);
		myCmdLine.AddCmd(&cmdFloatArgs);
		myCmdLine.AddCmd(&cmdDoubleArgs);
		myCmdLine.AddCmd(&cmdTestXMLEXP);
		myCmdLine.AddCmd(&cmdTestUserProps);
		myCmdLine.AddCmd(&myHelp);
		
		retVal = myCmdLine.Parse();

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

					QMessageBox msgBox;
					msgBox.setText(QCmdParseError::GetErrorString(retVal));
					QTimer::singleShot(6000, &msgBox, SLOT(accept()));
					msgBox.exec();

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

				QMessageBox msgBox;
				msgBox.setText(e->GetErrorString());
				QTimer::singleShot(6000, &msgBox, SLOT(accept()));
				msgBox.exec();

				e->Delete();

				retVal = -1;

				std::cout << "FAILED" << std::endl;
			}
		}
	}
	catch( QCmdParseException* e) {
		std::cout << e->GetErrorString().toStdString() << std::endl;

		QMessageBox msgBox;
		msgBox.setText(e->GetErrorString());
		QTimer::singleShot(6000, &msgBox, SLOT(accept()));
		msgBox.exec();

		e->Delete();

		retVal = -1;

		std::cout << "FAILED" << std::endl;
	}

	return retVal;
}
