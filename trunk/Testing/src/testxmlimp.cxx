#include "qbuBase/Property.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdParseException.h"
#include "qbuCmdLine/QCmdHelpException.h"
#include "qbuBase/PropertyMap.h"
#include <iostream>
#include <QDate>
#include "testxmlimp.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestXMLImport::QCmdTestXMLImport(QString strName, QString strDescription) :
	QCmd(strName,strDescription)
{
	int nTest = 0;
	AddArg("Test","Run test #","",nTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test0()
{
	QString testXML("<xml ty=\"127\"><RMTPatientID>HB016603</RMTPatientID></xml>");
	PropertyMap map;
	bool retVal = map.fromXML(testXML);
	if (retVal) {
		retVal = (map.size() == 1);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int  QCmdTestXMLImport::Execute()
{
	int nTest;

	GetArg("Test",nTest);

	bool bVal;
	switch(nTest) {
	case 0:
		bVal = test0();
		break;
	default:
		bVal = false;
	}

	return bVal ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS
