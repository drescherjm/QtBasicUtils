#include "cmdTestFloatOpts.h"
#include <QString>
#include <iostream>
#include "qbuCmdLine/QCmd.h"
#include "qbuCmdLine/QCmdParseError.h"

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestFloatOpts::QCmdTestFloatOpts(QString strName, QString strDescription) :
QCmd(strName,strDescription)
{
	AddArg("CaseNumber","The case number","",(quint32)0);

	float fTemp = 32.0f;
	AddOpt("T","Temperature","Temperature in Fahrenheit",fTemp);

	quint16 nTest = AllTests;
	AddOpt("test","The test number","",nTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestFloatOpts::Execute()
{
	quint16 nTest = 0;
	int retVal = GetOpt("test",nTest);

	if (QCmdParseError::Succeeded(retVal)) {
		retVal = runTest(nTest);
	}

	return QCmdParseError::STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestFloatOpts::runTest( int nTest )
{
	int retVal = (nTest < NUM_TESTS) ? QCmdParseError::STATUS_OK : QCmdParseError::PARAM_INVALID_DATA;
	if (QCmdParseError::Succeeded(retVal)) {
		switch(nTest) {
		case AllTests:
			for(int i=1; i < NUM_TESTS;++i) {
				int nCode = runTest(i);
				if ( !QCmdParseError::Succeeded(nCode) ) {
					retVal = nCode;
				}

				std::cerr << "qbuCmdLine/QCmdTestFloatOpts::runTest failed at test " << i << std::endl;

			}
			break;
		case TempExample:
			{
				quint32 nCase;
				GetArg("CaseNumber",nCase);

				std::cout << "CaseNumber=" << nCase << std::endl;

				float fTemp = 100.0f;
				GetOpt("T",fTemp);

				std::cout << "Temperature=" << fTemp << std::endl;
			}

			break;
		}
	}
	return retVal;
}
