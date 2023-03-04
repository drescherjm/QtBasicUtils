#include <iostream>

#include "qbuCmdLine/QCmd.h"
#include "qbuCmdLine/QCmdHelp.h"
#include "qbuCmdLine/QCmdLine.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdParseException.h"
#include "qbuCmdLine/QCmdHelpException.h"
#include "testxml.h"
#include "testUserProps.h"
#include <QMessageBox>
#include <QApplication>
#include <QTimer>

#include <math.h>
#include "qbuBase/qbuPropertyMap.h"
#include "qbuBase/qbuPropertyList.h"
#include "testxmlimp.h"
#include "testCommandLineInclude.h"
#include "testSetVariable.h"
#include "cmdTestFloatOpts.h"
#include "testxmlperf.h"
#include "testDBExpression.h"

#ifdef QBU_BUILD_DATABASE

/////////////////////////////////////////////////////////////////////////////////////////

#include "qbuDataBase/qbuDatabaseFunctions.h"

class QCmdTestSingleQuote : public QCmd
{
public:
	QCmdTestSingleQuote(QString strName, QString strDescription);
	virtual int Execute();
protected:
	bool	isQuoted(QString str);
	QString quoteIfNecissary(QString str);
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestSingleQuote::QCmdTestSingleQuote(QString strName, QString strDescription) : 
	QCmd(strName,strDescription)
{
	bool bQuote = true;
	AddOpt("quote_expected", "Give the expected value", "", bQuote);
	QString strMsg;
	AddArg("string", "The string to test", "For testing consistency between command line and CTest execution the outer quotes of this string are removed.", strMsg);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestSingleQuote::Execute()
{
	bool bQuote = false;
	int retVal = GetOpt("quote_expected", bQuote);

	if (QCmdParseError::Succeeded(retVal)) {
		QString str;
		retVal = GetArg("string", str, QCmd::REMOVE_OUTER_QUOTES);

		QString strOut = quoteIfNecissary(str);

		bool bIsQuoted = isQuoted(strOut);

		if (bIsQuoted != bQuote) {
			retVal = QCmdParseError::USER_EXECUTION_ERROR;
		}

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool QCmdTestSingleQuote::isQuoted(QString str)
{
	return str.startsWith("\'") && str.endsWith("\'");
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdTestSingleQuote::quoteIfNecissary(QString str)
{
	return ::singleQuoteIfNecissary(str);
}

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdTestSingleQuote1 : public QCmd
{
public:
	QCmdTestSingleQuote1(QString strName, QString strDescription);
	virtual int Execute();
protected:
	bool	isQuoted(QString str);
	QString quoteIfNecissary(QString str);
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestSingleQuote1::QCmdTestSingleQuote1(QString strName, QString strDescription) :
QCmd(strName, strDescription)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestSingleQuote1::Execute()
{
	bool bQuote = true;
	
	int retVal = QCmdParseError::STATUS_OK;
	
	QString str = " ";

	QString strOut = quoteIfNecissary(str);

	bool bIsQuoted = isQuoted(strOut);

	if (bIsQuoted != bQuote) {
		retVal = QCmdParseError::USER_EXECUTION_ERROR;
	}
	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool QCmdTestSingleQuote1::isQuoted(QString str)
{
	return str.startsWith("\'") && str.endsWith("\'");
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdTestSingleQuote1::quoteIfNecissary(QString str)
{
	return ::singleQuoteIfNecissary(str);
}

/////////////////////////////////////////////////////////////////////////////////////////



#endif //def QBU_BUILD_DATABASE

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdTestPropertyMapSimple : public QCmd
{
public:
	QCmdTestPropertyMapSimple(QString strName, QString strDescription);
	virtual int Execute();
public:
	int testIterator();
	int testConstIterator();
public:
	enum { TEST_ITERATOR=0,TEST_CONST_ITERATOR=1 };
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestPropertyMapSimple::QCmdTestPropertyMapSimple( QString strName, QString strDescription ) :
	QCmd(strName,strDescription)
{
	AddArg("TestNumber","The test number","",(quint32)TEST_CONST_ITERATOR);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestPropertyMapSimple::Execute()
{
	int retVal = QCmdParseError::USER_EXECUTION_ERROR;
	quint32 nTest;
	GetArg("TestNumber",nTest);

	switch (nTest) {
	case TEST_ITERATOR:
		retVal = testIterator();
		break;
	case TEST_CONST_ITERATOR:
		retVal = testConstIterator();
		break;
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestPropertyMapSimple::testConstIterator()
{
	qbuPropertyMap map;
	qbuPropertyMap::const_iterator it = map.find("Test");

	int retVal = (it == map.end()) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestPropertyMapSimple::testIterator()
{
	qbuPropertyMap map;
	qbuPropertyMap::iterator it = map.find("Test");

	int retVal = (it == map.end()) ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;

	return retVal;
}

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

class QCmdStringOpt : public QCmd
{
public:
	QCmdStringOpt(QString strName, QString strDescription, int nStrings=5);
	virtual int Execute();
protected:
	int m_nStrings;
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdStringOpt::QCmdStringOpt( QString strName, QString strDescription,int nStrings ) :
QCmd(strName,strDescription) , m_nStrings(nStrings)
{
	QString str;
	for(int i=0; i < nStrings; ++i) {
		AddOpt(QString("S%1").arg(i),QString("String # %1").arg(i),"",str);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdStringOpt::Execute()
{	
	int retVal = QCmdParseError::STATUS_OK;
	
	QString* strings = new QString[m_nStrings];
	
	for(int i=0; i < m_nStrings; ++i) {
		GetOpt(QString("S%1").arg(i),strings[i]);
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdUnitTest : public QCmd
{
public:
	QCmdUnitTest(QString strName, QString strDescription, int nStrings=5);
	virtual int Execute();
public:
	void	setVarToUpdate(bool * pBool);
protected:
	bool*	m_pUnitTesting;
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdUnitTest::QCmdUnitTest( QString strName, QString strDescription,int nStrings ) :
QCmd(strName,strDescription) 
{
	m_pUnitTesting = false;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdUnitTest::Execute()
{	
	if (m_pUnitTesting != NULL) {
		*m_pUnitTesting = true;
	}
	return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdUnitTest::setVarToUpdate( bool * pBool )
{
	m_pUnitTesting = pBool;
}

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdTestInvalidOptBadAddOpt0 : public QCmd
{
public:
	QCmdTestInvalidOptBadAddOpt0(QString strName, QString strDescription);
	virtual int Execute();
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestInvalidOptBadAddOpt0::QCmdTestInvalidOptBadAddOpt0( QString strName, QString strDescription) : 
QCmd(strName,strDescription)
{
	bool bTest = true;
	AddOpt("--test","This is a test","",bTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestInvalidOptBadAddOpt0::Execute()
{
	return QCmdParseError::STATUS_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////

class QCmdTestInvalidOptBadAddOpt1 : public QCmd
{
public:
	QCmdTestInvalidOptBadAddOpt1(QString strName, QString strDescription);
	virtual int Execute();
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestInvalidOptBadAddOpt1::QCmdTestInvalidOptBadAddOpt1( QString strName, QString strDescription) : 
QCmd(strName,strDescription)
{
	bool bTest = true;
	AddOpt("test+","This is a test","",bTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestInvalidOptBadAddOpt1::Execute()
{
	return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdTestInvalidOptBadAddOpt3 : public QCmd
{
public:
	QCmdTestInvalidOptBadAddOpt3(QString strName, QString strDescription);
	virtual int Execute();
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestInvalidOptBadAddOpt3::QCmdTestInvalidOptBadAddOpt3( QString strName, QString strDescription) : 
QCmd(strName,strDescription)
{
	bool bTest = true;
	AddOpt("test","This is a test","",bTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestInvalidOptBadAddOpt3::Execute()
{
	return QCmdParseError::STATUS_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////

class QCmdTestInvalidOpt : public QCmd
{
public:
	QCmdTestInvalidOpt(QString strName, QString strDescription);
	virtual int Execute();
};

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestInvalidOpt::QCmdTestInvalidOpt( QString strName, QString strDescription) : 
	QCmd(strName,strDescription)
{
	QStringList sl; 
	sl << "BADADDOPT0" << "BADADDOPT1" << "GOODADDOPT0";
	AddOpt("tests","Enter the subcommand to test.","",sl);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestInvalidOpt::Execute()
{
	QCoreApplication *pApp = QCoreApplication::instance();
	if (pApp != NULL) {
		QStringList lstCmdLine;
		QCmdLine cmdline(pApp->applicationName(),lstCmdLine);

		QStringList slTests;
		GetOpt("tests",slTests);

		if (slTests.contains("BADADDOPT0",Qt::CaseInsensitive)) {
			QCmdTestInvalidOptBadAddOpt0 myCmdTestInvalidOptInt("BADADDOPT0","This command tests an invalid option name containing a -.");
			cmdline.AddCmd(&myCmdTestInvalidOptInt);
		}

		if (slTests.contains("BADADDOPT1",Qt::CaseInsensitive)) {
			QCmdTestInvalidOptBadAddOpt1 myCmdTestInvalidOptInt("BADADDOPT1","This command tests an invalid option name containing a +.");
			cmdline.AddCmd(&myCmdTestInvalidOptInt);
		}

		if (slTests.contains("GOODADDOPT0",Qt::CaseInsensitive)) {
			QCmdTestInvalidOptBadAddOpt3 myCmdTestInvalidOptInt("GOODADDOPT0","This command tests a good option..");
			cmdline.AddCmd(&myCmdTestInvalidOptInt);
		}

	}

	return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	
	int retVal =0;

	QApplication app(argc, argv);

	bool bUnitTestting = false;

	try {
		QCmdUnitTest		cmdUnitTest("UT","Activate unit testing.");
		cmdUnitTest.setVarToUpdate(&bUnitTestting);

		QCmdEnter			cmdEnter("PAUSE","Use this to require user to press enter to exit." );
		QCmdTest			cmdTest("Test","This is the test command");
		QCmdStringListArg	cmdStrLstArg("STRLSTARG","This tests the string list as an argument.");
		QCmdStringListOpt	cmdStrLstOpt("STRLSTOPT","This tests the string list as an option.");
		QCmdOptBoolTest		cmdBoolOpt("BOOLOPT","This tests the bool an option.");
		QCmdOptExtBoolTest	cmdExtBoolOpt("EXTBOOLOPT","This tests the bool an extended option.");
		QCmdExtOpt			cmdExtOpt("EXTOPT","This tests the extended options.");
		QCmdTestPropertyMapSimple cmdTestPropertyMap("PROPMAP","This command tests the property map.");

		QCmdFloatArgs		cmdFloatArgs("FLOATARGS","This tests float as an arguments.");
		QCmdDoubleArgs		cmdDoubleArgs("DOUBLEARGS","This tests double as an arguments.");
		QCmdTestXMLExport	cmdTestXMLEXP("XMLEXP","This tests various exports of xml on the qbuProperty class.");
		QCmdTestXMLImport	cmdTestXMLIMP("XMLIMP","This tests various imports of xml on the qbuProperty class.");
		QCmdTestUserProps	cmdTestUserProps("USERPROP","This tests various exports of examples of using UserProps with the qbuProperty class.");
		QCmdStringOpt		cmdStringOpt2("STRINGOPT2","This command accepts 2 optional strings.",2);
		QCmdStringOpt		cmdStringOpt5("STRINGOPT5","This command accepts 5 optional strings.",5);

		QCmdTestFloatOpts	cmdFloatOpts("FLOATOPTS","This command tests float arguments.");

		CmdTestSetVar		cmdTestSETVariable("SET","This command tests command parsing of set commands.");


		QCmdTestInvalidOpt  cmdTestInvalidOpt("INVALIDCMDOPT","This command tests invalid options.");
		QCmdTestCmdLineFileInclude	cmdTestCmdLineFileInclude("CMDLINEINCLUDE","This tests the @ include that is used in the command line.");

        QCmdTestXMLPerformance cmdTestXMLPerf("XMLPERF", "This command helps profile the performance of the toXML and fromXML.");

		QCmdLine myCmdLine(argc,argv);
		QCmdHelp myHelp("This command shows the help message for all commands.","");

		myCmdLine.AddCmd(&cmdUnitTest);
		myCmdLine.AddCmd(&cmdEnter);
		myCmdLine.AddCmd(&cmdTest);
		myCmdLine.AddCmd(&cmdTestPropertyMap);
		myCmdLine.AddCmd(&cmdStrLstArg);
		myCmdLine.AddCmd(&cmdStrLstOpt);
		myCmdLine.AddCmd(&cmdBoolOpt);
		myCmdLine.AddCmd(&cmdExtBoolOpt);
		myCmdLine.AddCmd(&cmdExtOpt);
		myCmdLine.AddCmd(&cmdFloatArgs);
		myCmdLine.AddCmd(&cmdDoubleArgs);
		myCmdLine.AddCmd(&cmdTestXMLEXP);
		myCmdLine.AddCmd(&cmdTestXMLIMP);
		myCmdLine.AddCmd(&cmdTestUserProps);
		myCmdLine.AddCmd(&cmdStringOpt2);
		myCmdLine.AddCmd(&cmdStringOpt5);
		myCmdLine.AddCmd(&cmdTestInvalidOpt);
		myCmdLine.AddCmd(&cmdTestCmdLineFileInclude);
		myCmdLine.AddCmd(&cmdTestSETVariable);
        myCmdLine.AddCmd(&cmdTestXMLPerf);

		myCmdLine.AddCmd(&cmdFloatOpts);
		
#ifdef QBU_BUILD_DATABASE
		QCmdTestSingleQuote		cmdTestSingleQuote("DBSINGLEQUOTE", "Test the database singleQuoteIfNecissary() member");
		myCmdLine.AddCmd(&cmdTestSingleQuote);
		QCmdTestSingleQuote1	cmdTestSingleQuote1("DBSINGLEQUOTE_1", "Test the database singleQuoteIfNecissary() member for a single space.");
		myCmdLine.AddCmd(&cmdTestSingleQuote1);
		CmdTestDBExpression	cmdTestDBExpression("DBExpression", "This command tests the DBExpression class.");
		myCmdLine.AddCmd(&cmdTestDBExpression);
#endif // def QBU_BUILD_DATABASE

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
					std::cerr << QCmdParseError::GetErrorString(retVal).toStdString() << std::endl;
					
					if (!bUnitTestting) {
						QMessageBox msgBox;
						msgBox.setText(QCmdParseError::GetErrorString(retVal));
						QTimer::singleShot(6000, &msgBox, SLOT(accept()));
						msgBox.exec();
					}

				}
				if (retVal == QCmdParseError::STATUS_OK) {
					std::cout << "Succeeded" << std::endl;
				}
				else{
					std::cout << "FAILED" << std::endl;
				}
			}
			catch( QCmdParseException* e) {
				std::cerr << e->GetErrorString().toStdString() << std::endl;

				if (!bUnitTestting) {
					QMessageBox msgBox;
					msgBox.setText(e->GetErrorString());
					QTimer::singleShot(6000, &msgBox, SLOT(accept()));
					msgBox.exec();
				}

				e->Delete();

				retVal = -1;

				std::cout << "FAILED" << std::endl;
			}
		}
	}
	catch( QCmdParseException* e) {
		std::cout << e->GetErrorString().toStdString() << std::endl;

		if (!bUnitTestting) {
			QMessageBox msgBox;
			msgBox.setText(e->GetErrorString());
			QTimer::singleShot(6000, &msgBox, SLOT(accept()));
			msgBox.exec();
		}

		e->Delete();

		retVal = -1;

		std::cout << "FAILED" << std::endl;
	}

	return retVal;
}
