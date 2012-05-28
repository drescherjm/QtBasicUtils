#include "testCommandLineInclude.h"
#include "QCmdParseError.h"

/////////////////////////////////////////////////////////////////////////////////////////

QTUTILS::QCmdTestCmdLineFileInclude::QCmdTestCmdLineFileInclude( QString strName, QString strDescription ) : 
	QCmd(strName,strDescription)
{
	int nTest =0;
	AddOpt("test","Test Number","The test to run",nTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QTUTILS::QCmdTestCmdLineFileInclude::Execute()
{
	int nTest;
	int retVal = GetOpt("test",nTest);
	if (QCmdParseError::SUCCEEDED(retVal)) {
		retVal = runTest(nTest);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QTUTILS::QCmdTestCmdLineFileInclude::runTest( int nTest )
{
	int retVal = QCmdParseError::STATUS_OK;
	switch(nTest) {
	case ALL_TESTS:
		for(int i=1;i < NUM_TESTS;++i) {
			retVal = runTest(i);
			if (QCmdParseError::SUCCEEDED(retVal)) {
				break;
			}
		}
		break;
	case DOUBLE_QUOTES_1:
		retVal = runTest_DoubleQuotes_1();
		break;
	default:
		retVal = QCmdParseError::NOT_IMPLEMENTED;
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

int QTUTILS::QCmdTestCmdLineFileInclude::runTest_DoubleQuotes_1()
{

}

/////////////////////////////////////////////////////////////////////////////////////////
