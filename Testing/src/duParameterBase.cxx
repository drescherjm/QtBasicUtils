#include "duParameterBase.h"
#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuProperyMapXMLHelper.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int                                   m_nMetaIDPB = qRegisterMetaType<duParameterBase>();
static qbuProperyMapXMLHelper                hlprPB(m_nMetaIDPB);

static int                                   m_nMetaIDPBPtr = qRegisterMetaType<duParameterBase*>();
static qbuUserPropPtrHelper<duParameterBase> ptrHlprPB(m_nMetaIDPBPtr);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_DU_SET(className, variableName, variableType, strColumName)                                          \
	bool className::set##variableName(variableType _value) {                                                           \
		qbuProperty prop;                                                                                              \
		prop.setObjectName(strColumName);                                                                              \
		prop.SetData(_value);                                                                                          \
                                                                                                                       \
		return (insert(prop) != end());                                                                                \
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_DU_GET(className, variableName, variableType, strColumName)                                          \
	bool className::get##variableName(variableType& _value) {                                                          \
		bool retVal;                                                                                                   \
		retVal = className::getField<variableType>(strColumName, _value);                                              \
		return retVal;                                                                                                 \
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_DU_GET_VARIANT(className, variableName, strColumName)                                                \
	bool className::get##variableName(QVariant& _value) {                                                              \
		bool retVal;                                                                                                   \
		retVal = className::getField(strColumName, _value);                                                            \
		return retVal;                                                                                                 \
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString PARAM_DEFAULT("Default");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool duParameterBase::setDisplayName(QString strDisplayName) {
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool duParameterBase::setDefaultValue(QVariant vtValue) {
	QString strOld;
	bool    retVal = true;

	bool    bNotify = retVal;

	if (getDefaultValue(strOld)) {
		bNotify = (strOld != vtValue);
	}

	// Only update if the value actually changed..
	if (bNotify) {
		qbuProperty prop;
		prop.setObjectName(PARAM_DEFAULT);
		prop.SetData(vtValue);
		retVal = (insert(prop) != end());
	}

	return retVal;
}

IMPLEMENT_DU_GET(duParameterBase, DefaultValue, QString, PARAM_DEFAULT);
