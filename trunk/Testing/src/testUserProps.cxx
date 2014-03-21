/////////////////////////////////////////////////////////////////////////////////////////

#include "testUserProps.h"
#include "qbuCmdLine/QCmdParseError.h"

#include "qbuBase/Property.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdParseException.h"
#include "qbuCmdLine/QCmdHelpException.h"
#include "qbuBase/PropertyMap.h"
#include "qbuBase/PropertyList.h"
#include <iostream>
#include <QDate>

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

QCmdTestUserProps::QCmdTestUserProps(QString strName, QString strDescription) :
	QCmd(strName,strDescription)
{
	int nTest = 0;
	AddArg("Test","Run test #","",nTest);
}

/////////////////////////////////////////////////////////////////////////////////////////


static bool add_John(PropertyMap* pPM)
{
	bool retVal = (pPM != NULL);

	if (retVal) {
		Property prop;

		prop.SetData((int)37);
		prop.setObjectName("Age");
		retVal = (pPM->insert(prop) != pPM->end());

		if (retVal) {
			prop.SetData(QChar('M'));
			prop.setObjectName("Sex");
			pPM->insert(prop);
			retVal = (pPM->insert(prop) != pPM->end());

			if (retVal) {
				prop.SetData(QString("John M. Drescher"));
				prop.setObjectName("Name");
				pPM->insert(prop);
				retVal = (pPM->insert(prop) != pPM->end());
				
				if (retVal) {
					prop.SetData(QDate(1972,1,10));
					prop.setObjectName("DOB");
					pPM->insert(prop);
				}
				
			}
			
		}
		
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool add_John(PropertyList* pPL)
{
	bool retVal = (pPL != NULL);

	if (retVal) {
		Property prop;

		prop.SetData((int)37);
		prop.setObjectName("Age");
		pPL->push_back(prop);

		prop.SetData(QChar('M'));
		prop.setObjectName("Sex");
		pPL->push_back(prop);

		prop.SetData(QString("John M. Drescher"));
		prop.setObjectName("Name");
		pPL->push_back(prop);

		prop.SetData(QDate(1972,1,10));
		prop.setObjectName("DOB");
		pPL->push_back(prop);
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool add_Kathy(PropertyMap* pPM)
{
	bool retVal = (pPM != NULL);

	if (retVal) {
		Property prop;

		prop.SetData((int)40);
		prop.setObjectName("Age");
		pPM->insert(prop);
		retVal = (pPM->insert(prop) != pPM->end());
	
		if (retVal) {
			prop.SetData(QChar('F'));
			prop.setObjectName("Sex");
			pPM->insert(prop);
			retVal = (pPM->insert(prop) != pPM->end());
			
			if (retVal) {
				prop.SetData(QString("Kathy M. Zorn"));
				prop.setObjectName("Name");
				pPM->insert(prop);
				retVal = (pPM->insert(prop) != pPM->end());
				
				if (retVal) {
					prop.SetData(QDate(1969,1,13));
					prop.setObjectName("DOB");
					pPM->insert(prop);
					retVal = (pPM->insert(prop) != pPM->end());
				}
			}
		}
		
	}
	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool add_Kathy(PropertyList* pPL)
{
	bool retVal = (pPL != NULL);

	if (retVal) {
		Property prop;

		prop.SetData((int)40);
		prop.setObjectName("Age");
		pPL->push_back(prop);

		prop.SetData(QChar('F'));
		prop.setObjectName("Sex");
		pPL->push_back(prop);

		prop.SetData(QString("Kathy M. Zorn"));
		prop.setObjectName("Name");
		pPL->push_back(prop);

		prop.SetData(QDate(1969,1,13));
		prop.setObjectName("DOB");
		pPL->push_back(prop);
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test0()
{
	bool retVal;
	PropertyMap* pPM = new PropertyMap;
	retVal = (pPM != NULL);
	
	if (retVal) {
		UserPropPtr ptr(pPM);
		retVal = add_John(pPM);

		if (retVal) {
			QString strXML0 = pPM->toXML();

			PropertyMap pm1;
			retVal = add_John(&pm1);
			if (retVal) {
				QString strXML1 = pm1.toXML();

				retVal =(strXML0.compare(strXML1) == 0);
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test1()
{
	bool retVal;
	PropertyMap* pPM = new PropertyMap;
	retVal = (pPM != NULL);

	if (retVal) {
		UserPropPtr ptr(pPM);
		retVal = add_John(dynamic_cast<PropertyMap*>(ptr.data()));

		if (retVal) {
			QString strXML0 = pPM->toXML();

			PropertyMap pm1;
			retVal = add_John(&pm1);
			if (retVal) {
				QString strXML1 = pm1.toXML();

				retVal =(strXML0.compare(strXML1) == 0);
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test2()
{
	bool retVal;
	PropertyMap* pPM = new PropertyMap;
	retVal = (pPM != NULL);

	if (retVal) {
		Property	prop;
		UserPropPtr ptr(pPM);
		retVal = add_John(dynamic_cast<PropertyMap*>(ptr.data()));
		prop.SetData(ptr);

		if (retVal) {

			QString strXML0 = pPM->toXML();

			PropertyMap pm1;
			retVal = add_John(&pm1);
			if (retVal) {
				QString strXML1 = pm1.toXML();

				retVal =(strXML0.compare(strXML1) == 0);
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test3()
{
	bool retVal;
	PropertyMap* pPM = new PropertyMap;
	retVal = (pPM != NULL);

	if (retVal) {
		Property	prop;
		UserPropPtr ptr(pPM);
		retVal = add_John(dynamic_cast<PropertyMap*>(ptr.data()));
		prop.SetData(ptr);
		prop.setObjectName("Person0");

		if (retVal) {

			UserPropPtr ptr1 = prop;

			QString strXML0 = ptr1.toXML();

			PropertyMap pm1;
			retVal = add_John(&pm1);
			if (retVal) {
				QString strXML1 = pm1.toXML();

				retVal =(strXML0.compare(strXML1) == 0);
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test4()
{
	bool retVal;
	PropertyMap* pPM = new PropertyMap;
	retVal = (pPM != NULL);

	if (retVal) {
		Property	prop;
		UserPropPtr ptr(pPM);
		retVal = add_John(dynamic_cast<PropertyMap*>(ptr.data()));
		prop.SetData(ptr);
		prop.setObjectName("Person0");

		if (retVal) {

			QString strXML0 = prop.toXML();

			PropertyMap pm1;
			retVal = add_John(&pm1);
			if (retVal) {
				QString strXML1 = pm1.toXML();

				retVal =(strXML0.compare(strXML1) == 0);
			}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test5()
{
	bool retVal;
	PropertyMap* pPM = new PropertyMap;
	retVal = (pPM != NULL);

	if (retVal) {
		Property	prop;
		UserPropPtr ptr(pPM);
		retVal = add_John(dynamic_cast<PropertyMap*>(ptr.data()));
		prop.SetData(ptr);
		prop.setObjectName("Person0");

		if (retVal) {

			retVal = prop.Save("PMUserSave.xml");

			if (retVal) {
				Property prop1;
				prop1.Load("PMUserSave.xml");
			}

		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test6()
{
	bool retVal;
	PropertyList* pPList = new PropertyList;
	retVal = (pPList != NULL);

	if (retVal) {
		Property	prop;
		UserPropPtr ptr(pPList);
		retVal = add_John(dynamic_cast<PropertyList*>(ptr.data()));
		prop.SetData(ptr);
		prop.setObjectName("Person0");

		if (retVal) {

			retVal = prop.Save("PLUserSave.xml");

			if (retVal) {
				Property prop1;
				retVal = prop1.Load("PLUserSave.xml");
				if (retVal) {
					QString strXML0 = prop.toXML();
					QString strXML1 = prop1.toXML();

					retVal =(strXML0.compare(strXML1) == 0);
				}
			}

		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test7()
{
	bool retVal;
	PropertyList* pPList = new PropertyList;
	retVal = (pPList != NULL);

	if (retVal) {
		Property	prop;
		UserPropPtr ptr(pPList);

		retVal = add_John(dynamic_cast<PropertyList*>(ptr.data()));
		int nItems = pPList->size();
		prop.SetData(ptr);
		prop.setObjectName("Person0");

		if (retVal) {

			retVal = prop.Save("PLUserSave.xml");

			if (retVal) {
				Property prop1;
				retVal = prop1.Load("PLUserSave.xml");
				if (retVal) {
					QString strXML0 = prop.toXML();
					QString strXML1 = prop1.toXML();

					retVal =(strXML0.compare(strXML1) == 0);

					if (retVal) {
						UserPropPtr ptr1 = prop1;
						QExplicitlySharedDataPointer<PropertyList> pPL = ptr1.GetPtr();
						int nItems1=pPL.data()->size();
						retVal = (nItems == nItems1);
					}
				}
			}

		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test8()
{
	// These are to test the assignment operator.
	PropertyMap map1;
	add_John(&map1);

	PropertyMap map2;
	add_Kathy(&map2);

	map1 = map2;
	PropertyMap map3 = map2;

	PropertyMap map4(map1);

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

static bool test9()
{
	// These are to test the assignment operator.
	PropertyList list1;
	add_John(&list1);

	PropertyList list2;
	add_Kathy(&list2);

	list1 = list2;
	PropertyList list3 = list2;

	PropertyList list4(list1);

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdTestUserProps::Execute()
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

}; //namespace QTUTILS 
