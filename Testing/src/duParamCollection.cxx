#include "duParamCollection.h"
#include "duParameterBase.h"
#include "qbuBase/qbuProperyMapXMLHelper.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int                                     m_nMetaID = qRegisterMetaType<duParamCollection>();
static qbuProperyMapXMLHelper                  hlpr(m_nMetaID);

static int                                     m_nMetaIDPtr = qRegisterMetaType<duParamCollection*>();
static qbuUserPropPtrHelper<duParamCollection> ptrHlpr(m_nMetaIDPtr);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

duParamCollection::duParamCollection() : qbuPropertyMap() {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

duParamCollection::duParamCollection(const duParamCollection& other) : qbuPropertyMap(other) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::iterator duParamCollection::insert(duParameterBase* pParam, bool bAutoDelete /*= true*/) {
	duParamCollection::iterator retVal = end();

	if (pParam != nullptr) {

		if (duVarName::isValidVariableName(pParam->objectName())) {
			qbuUserPropPtr ptr(pParam, bAutoDelete);

			qbuProperty    prop;
			prop.setObjectName(pParam->objectName());
			prop.SetData(ptr);
			retVal = Superclass::insert(prop);

			if (retVal != end()) {
				connectSignals(pParam);
				emit valueChanged(pParam);
			}
		} else {
			emit warning("A variable will be ignored because its name is INVALID.");
		}
	}

	return retVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void duParamCollection::connectSignals(duParameterBase* pParam) {
	// For this test, we don't need to connect any signals, but in a real implementation, you would connect the
	// necessary signals here.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
