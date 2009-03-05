#include "testxml.h"
#include "Property.h"
#include "QCmdParseError.h"
#include "QCmdParseException.h"
#include "QCmdHelpException.h"
#include "PropertyMap.h"
#include <iostream>
#include <QDate>

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

bool test4()
{

	QTUTILS::PropertyMap pmPeople,pmJohn, pmKathy;
	QTUTILS::Property prop;

	prop.setObjectName("Age");
	prop.GetData() = (int)37;
	pmJohn.insert(prop);

	prop.setObjectName("Name");
	prop.GetData() = QString("John M. Drescher");
	pmJohn.insert(prop);

	prop.setObjectName("Best Friend");
	prop.GetData() = QString("Kathy M. Zorn");
	pmJohn.insert(prop);

	prop.setObjectName("Sex");
	prop.GetData() = QChar('M');
	pmJohn.insert(prop);

	prop.setObjectName("Person0");
	prop.GetData() = QVariant::fromValue(pmJohn);
	pmPeople.insert(prop);

	prop.setObjectName("Age");
	prop.GetData() = (int)40;
	pmKathy.insert(prop);

	prop.setObjectName("Name");
	prop.GetData() = QString("Kathy M. Zorn");
	pmKathy.insert(prop);

	prop.setObjectName("Best Friend");
	prop.GetData() = QString("John M. Drescher");
	pmKathy.insert(prop);

	prop.setObjectName("Sex");
	prop.GetData() = QChar('F');
	pmKathy.insert(prop);

	prop.setObjectName("Person1");
	prop.GetData() = QVariant::fromValue(pmKathy);
	pmPeople.insert(prop);

	QString str = pmPeople.toXML();

	QTUTILS::PropertyMap pc1;

	bool retVal = pc1.fromXML(str);

	QString str1 = pc1.toXML();

	if (retVal) {
		retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
	}

	return retVal;	

}

/////////////////////////////////////////////////////////////////////////////////////////

bool test5()
{

	QTUTILS::PropertyMap pmPeople,pmJohn, pmKathy;
	QTUTILS::Property prop;

	prop.setObjectName("Age");
	prop.GetData() = (int)37;
	pmJohn.insert(prop);

	prop.setObjectName("Name");
	prop.GetData() = QString("John M. Drescher");
	pmJohn.insert(prop);

	prop.setObjectName("Best Friend");
	prop.GetData() = QString("Kathy M. Zorn");
	pmJohn.insert(prop);

	prop.setObjectName("Sex");
	prop.GetData() = QChar('M');
	pmJohn.insert(prop);

	prop.setObjectName("DOB");
	prop.GetData() = QDate(1972,1,10);
	pmJohn.insert(prop);

	prop.setObjectName("Some Extra data");
	prop.GetData() = (float)-1.222;
	pmJohn.insert(prop);

	prop.setObjectName("Person0");
	prop.GetData() = QVariant::fromValue(pmJohn);
	pmPeople.insert(prop);

	prop.setObjectName("Age");
	prop.GetData() = (int)40;
	pmKathy.insert(prop);

	prop.setObjectName("Name");
	prop.GetData() = QString("Kathy M. Zorn");
	pmKathy.insert(prop);

	prop.setObjectName("Best Friend");
	prop.GetData() = QString("John M. Drescher");
	pmKathy.insert(prop);

	prop.setObjectName("Sex");
	prop.GetData() = QChar('F');
	pmKathy.insert(prop);

	prop.setObjectName("DOB");
	prop.GetData() = QDate(1969,1,13);
	pmKathy.insert(prop);

	prop.setObjectName("Person1");
	prop.GetData() = QVariant::fromValue(pmKathy);
	pmPeople.insert(prop);

	QString str = pmPeople.toXML();
	bool retVal = pmPeople.Save("People.xml");
	if (retVal) {
		QTUTILS::PropertyMap pc1;

		retVal = pc1.Load("People.xml");

		QString str1 = pc1.toXML();

		if (retVal) {
			retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
		}
	}

	return retVal;	
}

/////////////////////////////////////////////////////////////////////////////////////////

bool test6()
{
	//This tests the update tracking of PropertyMap

	QTUTILS::PropertyMap pmPeople,pmJohn, pmKathy;
	QTUTILS::Property prop;

	bool retVal = !pmJohn.HasChanged();

	if (retVal) {
		prop.setObjectName("Age");
		prop.GetData() = (int)37;
		pmJohn.insert(prop);
		
		retVal = pmJohn.HasChanged();

		if (retVal) {
			
			pmJohn.ForceUnmodified();

			retVal = !pmJohn.HasChanged();

			if (retVal) {
				prop.setObjectName("Name");
				prop.GetData() = QString("John M. Drescher");
				pmJohn.insert(prop);


				prop.setObjectName("Best Friend");
				prop.GetData() = QString("Kathy M. Zorn");
				pmJohn.insert(prop);

				prop.setObjectName("Sex");
				prop.GetData() = QChar('M');
				pmJohn.insert(prop);

				retVal = pmJohn.HasChanged();
			}

		}		
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
	case 4:
		bVal = test4();
		break;
	case 5:
		bVal = test5();
		break;
	case 6:
		bVal = test6();
		break;
	default:
		bVal = false;
	}

	return bVal ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS