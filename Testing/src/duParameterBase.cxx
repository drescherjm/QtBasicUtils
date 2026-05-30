#include "duParameterBase.h"
#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuProperyMapXMLHelper.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int                                   m_nMetaIDPB = qRegisterMetaType<duParameterBase>();
static qbuProperyMapXMLHelper                hlprPB(m_nMetaIDPB);

static int                                   m_nMetaIDPBPtr = qRegisterMetaType<duParameterBase*>();
static qbuUserPropPtrHelper<duParameterBase> ptrHlprPB(m_nMetaIDPBPtr);

static int                                   m_nMetaID = qRegisterMetaType<duParameterBase::DicomNullBehavior>();

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
const QString PARAM_VALUE("Value");
const QString NULL_VALUE("NULL");
const QString PARAM_FIELD_WIDTH("FieldWidth");
const QString PARAM_MAX_FIELD_WIDTH("MaxFieldWidth");
const QString PARAM_MIN_FIELD_WIDTH("MinFieldWidth");
const QString PARAM_FIELD_ALIGNMENT("FieldAlignment");
const QString PARAM_PAD_CHAR("PadChar");

IMPLEMENT_DU_GET(duParameterBase, DefaultValue, QString, PARAM_DEFAULT);
IMPLEMENT_DU_GET_VARIANT(duParameterBase, Value, PARAM_VALUE);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool duParameterBase::setDisplayName(QString strDisplayName) {
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool duParameterBase::setValue(QVariant vtValue) {
	QVariant vtOld;
	bool     retVal;

	bool     bNotify = true;

	if (getValue(vtOld)) {
		bNotify = (vtOld != vtValue);
	}

	qbuProperty prop;
	prop.setObjectName(PARAM_VALUE);
	prop.SetData(vtValue);
	retVal = (insert(prop) != end());

	if (retVal && bNotify) {
		emit valueChanged(this);
	}

	return retVal;
}

bool duParameterBase::setValueToDefault() {
	bool retVal = hasField(PARAM_DEFAULT);
	if (retVal) {
		//		if (!hasFormat()) {
		CopyProperty(PARAM_DEFAULT, *this, PARAM_VALUE);
		// 		}
		// 		else
		// 		{
		// 			setValue(makeVariable(objectName()));
		// 		}
	}
	return retVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool duParameterBase::getValue(QString& strValue, bool bUseFormat, bool bValidate) {
	DicomNullBehavior dn{NB_DEFAULT};
	getDicomNullBehavior(dn);

	bool retVal = !bValidate;
	if (!retVal) {
		retVal = validate();
		if (!retVal) {
			if ((dn != NB_IGNORE) && (dn != NB_DELETE)) {
				emit validation_failed(this);
			}
		}
	}

	if (retVal) {
		retVal = getField<QString>(PARAM_VALUE, strValue);

		if (dn == NB_DELETE) {
			strValue.remove(duParameterBase::nullValue());
		}

		if ((bUseFormat) && hasFormat()) {
			strValue = formatValue(strValue);
		}
	}

	return retVal;
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

bool duParameterBase::getDicomNullBehavior(DicomNullBehavior& dn) {
	QString strVal;
	bool    retVal = getField<QString>("DicomNullBehavior", strVal);
	if (retVal) {
		if (strVal == "NB_WARN") {
			dn = NB_WARN;
		} else if (strVal == "NB_IGNORE") {
			dn = NB_IGNORE;
		} else if (strVal == "NB_DELETE") {
			dn = NB_DELETE;
		} else {
			dn = NB_DEFAULT;
		}
	}
	return retVal;
}

bool duParameterBase::setVariableValue(QString strVarName, QString strValRep) {
	strVarName  = strVarName.trimmed();
	bool retVal = !strVarName.isEmpty();
	if (retVal) {
		QString strVal;
		retVal = getValue(strVal);
		if (retVal) {
			if (!strVarName.startsWith('%')) {
				strVarName.prepend('%');
				strVarName.append('%');
			}
			QString strNewVal = strVal;
			strNewVal.replace(strVarName, strValRep, Qt::CaseInsensitive);
			if (strVal.compare(strNewVal) == 0) {
				// This means no substitution took place so we check to see if there
				// was a dependent variable strVarName already set.

				strVarName.remove('%');

				//	JMD: Disable this code since it causes unnecessary failure..
				// 				QStringList lst = getDependentVariables();
				// 				retVal = lst.contains(strVarName,Qt::CaseInsensitive);
				// 				if (!retVal) {
				// 					lst = getDependentVariables(DT_VALUE);
				// 					retVal = lst.contains(strVarName);
				// 				}
			} else {
				setValue(strNewVal);
			}
		}
	}
	return retVal;
}

bool duParameterBase::hasFormat() {
	return hasField(PARAM_FIELD_ALIGNMENT) || hasField(PARAM_FIELD_WIDTH) || hasField(PARAM_PAD_CHAR);
}

QString duParameterBase::nullValue() {
	const QString retVal = makeVariable(NULL_VALUE);
	return retVal;
}
