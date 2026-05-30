#include "testPropertyMemoryBug.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuBase/qbuUserPropPtr.h"
#include "qbuBase/qbuPropXMLHelper.h"
#include "qbuBase/qbuProperyMapXMLHelper.h"
#include "duParameterBase.h"
#include "duParamCollection.h"
#include "duParameter.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CmdTestPropertyMemoryBug::CmdTestPropertyMemoryBug(QString strName, QString strDescription)
    : QCmd(strName, strDescription) {

	int nTest = 0;
	AddArg("Test", "Run test #", "", nTest);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CmdTestPropertyMemoryBug::Execute() {
	int nTest;

	GetArg("Test", nTest);

	bool bVal;
	switch (nTest) {
	case 0:
		bVal = test0();
		break;
	case 1:
		bVal = test1();
		break;
	case 2:
		bVal = test2();
		break;
		// 	case 5:
		// 		bVal = test5();
		// 		break;
	default:
		bVal = false;
	}

	return bVal ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CmdTestPropertyMemoryBug::test0() {
	duParameterBase param;
	param.setObjectName("TestParam");
	param.setDefaultValue("TestValue");

	duParamCollection collection;

	collection.insert(&param,false);

	std::cout << "Collection XML: " << collection.toXML().toStdString() << std::endl;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CmdTestPropertyMemoryBug::test1() {
	duParameterBase param;
	param.setObjectName("TestParam");
	param.setDefaultValue("TestValue");

	duParamCollection collection;

	collection.insert(&param, false);

	std::cout << "Collection XML: " << collection.toXML().toStdString() << std::endl;


	duParamCollection collection2;

	collection2.fromXML(collection.toXML());

	std::cout << "Collection2 XML: " << collection2.toXML().toStdString() << std::endl;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CmdTestPropertyMemoryBug::test2() {
	duParameter param;
	QStringList lst;
	lst << "One" << "Two" << "Three";
	param.setObjectName("StringListParam");
	param.setDefaultValue(lst);
	param.setValueToDefault();
	QStringList       lstOut;

	duParamCollection coll;
	coll.insert(&param, false); // false allows the param to be on the stack.

	duParamCollection coll2;
	bool              bVal = coll2.fromXML(coll.toXML());

	if (bVal) {
		bVal = (coll2.size() == 1);
		if (!bVal) {
			std::cerr << "Collection size was not matched after XML round trip.";
		}

		auto pParam = coll2.getParamPtr<duParameter>("StringListParam");
		bVal        = (pParam != nullptr);

		if (bVal) {

			QStringList lstNames;

			QVariant    vt;
			bVal = pParam->getValue(vt);
			if (bVal) {
				lstNames = vt.toStringList();

				bVal = (lstNames.size() == 3);
				if (bVal) {
					bVal = ((lstNames[0] == "One") && (lstNames[1] == "Two") && (lstNames[2] == "Three"));
					if (!bVal) {
						std::cerr << "Parameter values were not matched after XML round trip.";
					}
				} else {
					std::cerr << "Not all parameter values were decoded after XML round trip.";
				}
			} else {
				std::cerr << "getValue returned a failure after XML round trip.";
			}
		}
	} else {
		std::cerr << "fromXML returned a failure.";
	}

#define DUMP_XML

#ifdef DUMP_XML
	std::cout << "Default value XML: " << qPrintable(coll2.toXML()) << std::endl;
#endif

	return bVal ? QCmdParseError::STATUS_OK : QCmdParseError::USER_EXECUTION_ERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
