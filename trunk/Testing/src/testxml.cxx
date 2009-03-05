#include "testxml.h"
#include "Property.h"
#include "QCmdParseError.h"
#include "QCmdParseException.h"
#include "QCmdHelpException.h"
#include "PropertyMap.h"
#include <iostream>

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestXMLExport::QCmdTestXMLExport(QString strName, QString strDescription) :
	QCmd(strName,strDescription)
{
	int nTest = 0;
	AddArg("Test","Run test #","",nTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool test_exportXML(QTUTILS::Property & prop) 
{
	std::cout << "BEGIN: Testing test_exportXML" << std::endl;

	QString strXML = prop.toXML();
	QTUTILS::Property prop1;
	prop1.fromXML(strXML);
	QString strXML1 = prop1.toXML();

	std::cout << "Prop= " <<  strXML.toStdString() << std::endl;
	std::cout << "Prop1= " << strXML1.toStdString() << std::endl;

	std::cout << "END: Testing test_exportXML" << std::endl;

	return (strXML.compare(strXML1) == 0);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool test0()
{

	QTUTILS::Property prop;

	prop.setObjectName("Name");
	prop.GetData() = QString("John M. Drescher");
	
	return test_exportXML(prop);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool test1()
{

	QTUTILS::Property prop;

	prop.setObjectName("Age");
	prop.GetData() = (int)37;
	
	return test_exportXML(prop);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool test2()
{

	QTUTILS::Property prop;

	prop.setObjectName("Sex");
	prop.GetData() = QChar('M');
	
	return test_exportXML(prop);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool test3()
{
	QTUTILS::PropertyMap pc;
	QTUTILS::Property prop;
	
	prop.setObjectName("Age");
	prop.GetData() = (int)37;
	pc.insert(prop);

	prop.setObjectName("Name");
	prop.GetData() = QString("John M. Drescher");
	pc.insert(prop);

	prop.setObjectName("Sex");
	prop.GetData() = QChar('M');
	pc.insert(prop);

	QString str = pc.toXML();

	QTUTILS::PropertyMap pc1;

	bool retVal = pc1.fromXML(str);

	QString str1 = pc1.toXML();

	if (retVal) {
		retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
	}
	
	return retVal;	
}

/////////////////////////////////////////////////////////////////////////////////////////

int  QCmdTestXMLExport::Execute()
{
	int nTest;

	GetArg("Test",nTest);

	bool bVal;
	switch(nTest) {
	case 0:
		bVal = test0();
		break;
	case 1:
		bVal = test1();
		break;
	case 2:
		bVal = test2();
		break;
	case 3:
		bVal = test3();
		break;
	default:
		bVal = false;
	}

	return bVal ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS