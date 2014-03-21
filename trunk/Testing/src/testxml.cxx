#include "testxml.h"
#include "qbuBase/Property.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdParseException.h"
#include "qbuCmdLine/QCmdHelpException.h"
#include "qbuBase/PropertyMap.h"
#include <iostream>
#include <QDate>
#include "qxml.h"
#include "qdebug.h"



/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestXMLExport::QCmdTestXMLExport(QString strName, QString strDescription) :
	QCmd(strName,strDescription)
{
	int nTest = 0;
	AddArg("Test","Run test #","",nTest);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool test_exportXML(Property & prop) 
{
	std::cout << "BEGIN: Testing test_exportXML" << std::endl;

	QString strXML = prop.toXML();
	Property prop1;
	prop1.fromXML(strXML);
	QString strXML1 = prop1.toXML();

	std::cout << "Prop= " <<  strXML.toStdString() << std::endl;
	std::cout << "Prop1= " << strXML1.toStdString() << std::endl;

	std::cout << "END: Testing test_exportXML" << std::endl;

	return (strXML.compare(strXML1) == 0);
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test0()
{

	Property prop;

	prop.setObjectName("Name");
	prop.SetData(QString("John M. Drescher"));
	
	return test_exportXML(prop);
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test1()
{

	Property prop;

	prop.setObjectName("Age");
	prop.SetData((int)37);
	
	return test_exportXML(prop);
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test2()
{

	Property prop;

	prop.setObjectName("Sex");
	prop.SetData(QChar('M'));
	
	return test_exportXML(prop);
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test3()
{
	PropertyMap pc;
	Property prop;
	
	prop.setObjectName("Age");
	prop.SetData((int)37);
	pc.insert(prop);

	prop.setObjectName("Name");
	prop.SetData(QString("John M. Drescher"));
	pc.insert(prop);

	prop.setObjectName("Sex");
	prop.SetData(QChar('M'));
	pc.insert(prop);

	QString str = pc.toXML();

	PropertyMap pc1;

	bool retVal = pc1.fromXML(str);

	QString str1 = pc1.toXML();

	if (retVal) {
		retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
	}
	
	return retVal;	
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test4()
{

	PropertyMap pmPeople,pmJohn, pmKathy;
	Property prop;

	prop.setObjectName("Age");
	prop.SetData((int)37);
	pmJohn.insert(prop);

	prop.setObjectName("Name");
	prop.SetData(QString("John M. Drescher"));
	pmJohn.insert(prop);

	prop.setObjectName("Best Friend");
	prop.SetData(QString("Kathy M. Zorn"));
	pmJohn.insert(prop);

	prop.setObjectName("Sex");
	prop.SetData(QChar('M'));
	pmJohn.insert(prop);

	prop.setObjectName("Person0");
	prop.SetData(QVariant::fromValue(pmJohn));
	pmPeople.insert(prop);

	prop.setObjectName("Age");
	prop.SetData((int)40);
	pmKathy.insert(prop);

	prop.setObjectName("Name");
	prop.SetData(QString("Kathy M. Zorn"));
	pmKathy.insert(prop);

	prop.setObjectName("Best Friend");
	prop.SetData(QString("John M. Drescher"));
	pmKathy.insert(prop);

	prop.setObjectName("Sex");
	prop.SetData(QChar('F'));
	pmKathy.insert(prop);

	prop.setObjectName("Person1");
	prop.SetData(QVariant::fromValue(pmKathy));
	pmPeople.insert(prop);

	QString str = pmPeople.toXML();

	PropertyMap pc1;

	bool retVal = pc1.fromXML(str);

	QString str1 = pc1.toXML();

	if (retVal) {
		retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
	}

	return retVal;	

}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test5()
{

	PropertyMap pmPeople,pmJohn, pmKathy;
	Property prop;

	prop.setObjectName("Age");
	prop.SetData((int)37);
	pmJohn.insert(prop);

	prop.setObjectName("Name");
	prop.SetData(QString("John M. Drescher"));
	pmJohn.insert(prop);

	prop.setObjectName("Best Friend");
	prop.SetData(QString("Kathy M. Zorn"));
	pmJohn.insert(prop);

	prop.setObjectName("Sex");
	prop.SetData(QChar('M'));
	pmJohn.insert(prop);

	prop.setObjectName("DOB");
	prop.SetData(QDate(1972,1,10));
	pmJohn.insert(prop);

	prop.setObjectName("Some Extra data");
	prop.SetData((float)-1.222);
	pmJohn.insert(prop);

	prop.setObjectName("Person0");
	prop.SetData(QVariant::fromValue(pmJohn));
	pmPeople.insert(prop);

	prop.setObjectName("Age");
	prop.SetData((int)40);
	pmKathy.insert(prop);

	prop.setObjectName("Name");
	prop.SetData(QString("Kathy M. Zorn"));
	pmKathy.insert(prop);

	prop.setObjectName("Best Friend");
	prop.SetData(QString("John M. Drescher"));
	pmKathy.insert(prop);

	prop.setObjectName("Sex");
	prop.SetData(QChar('F'));
	pmKathy.insert(prop);

	prop.setObjectName("DOB");
	prop.SetData(QDate(1969,1,13));
	pmKathy.insert(prop);

	prop.setObjectName("Person1");
	prop.SetData(QVariant::fromValue(pmKathy));
	pmPeople.insert(prop);

	QString str = pmPeople.toXML();
	bool retVal = pmPeople.Save("People.xml");
	if (retVal) {
		PropertyMap pc1;

		retVal = pc1.Load("People.xml");

		QString str1 = pc1.toXML();

		if (retVal) {
			retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
		}
	}

	return retVal;	
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test6()
{
	//This tests the update tracking of PropertyMap

	PropertyMap pmPeople,pmJohn, pmKathy;
	Property prop;

	bool retVal = !pmJohn.HasChanged();

	if (retVal) {
		prop.setObjectName("Age");
		prop.SetData((int)37);
		pmJohn.insert(prop);
		
		retVal = pmJohn.HasChanged();

		if (retVal) {
			
			pmJohn.ForceUnmodified();

			retVal = !pmJohn.HasChanged();

			if (retVal) {
				prop.setObjectName("Name");
				prop.SetData(QString("John M. Drescher"));
				pmJohn.insert(prop);


				prop.setObjectName("Best Friend");
				prop.SetData(QString("Kathy M. Zorn"));
				pmJohn.insert(prop);

				prop.setObjectName("Sex");
				prop.SetData(QChar('M'));
				pmJohn.insert(prop);

				retVal = pmJohn.HasChanged();
			}

		}		
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test7()
{
	QString testXML("<xml ty=\"127\"><RMTPatientID>HB016603</RMTPatientID></xml>");
	PropertyMap map;
	bool retVal = map.fromXML(testXML);
	if (retVal) {

	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test8()
{
	PropertyMap pc;
	Property prop;

	prop.setObjectName("Age");
	prop.SetData((int)37);
	pc.insert(prop);

	prop.setObjectName("Name");
	prop.SetData(QString("John M. Drescher"));
	pc.insert(prop);

	prop.setObjectName("Sex");
	prop.SetData(QChar(' '));
	pc.insert(prop);

	QString str = pc.toXML();

	PropertyMap pc1;

	bool retVal = pc1.fromXML(str);

	QString str1 = pc1.toXML();

	if (retVal) {
		retVal = (str.compare(str1,Qt::CaseInsensitive) == 0);
	}

	return retVal;	
}

static bool test9() 
{
	QString xmlString("<original>      </original>");
	QDomDocument doc;
	doc.setContent(xmlString);
	QDomElement docElem = doc.documentElement();
	qDebug() << "Without QXmlSimpleReader \t- element contains" <<docElem.text() << "\tlength="<< docElem.text().length();
	doc.clear();
	QXmlInputSource source;
	source.setData(xmlString);
	QXmlSimpleReader reader;
	doc.setContent(&source, &reader);
	docElem = doc.documentElement();
	qDebug() << "With QXmlSimpleReader \t- element contains" <<docElem.text() << "\tlength="<< docElem.text().length();

	return false;
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
	case 7:
		bVal = test7();
		break;
	case 8:
		bVal = test8();
		break;
	case 9:
		bVal = test9();
		break;
	default:
		bVal = false;
	}

	return bVal ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////


