#pragma once

#ifndef DUPARAMETERBASE_H
#define DUPARAMETERBASE_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "qbuBase/qbuPropertyMap.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class duVarName {
public:
	static bool isValidVariableName(const QString& strName) {
		bool retVal = !strName.isEmpty();
		if (retVal) {
			for (int i = 0; i < strName.size(); ++i) {
				QChar ch = strName.at(i);
				if (i == 0) {
					retVal = ch.isLetter() || (ch == '_');
				} else {
					retVal = ch.isLetterOrNumber() || (ch == '_');
				}
				if (!retVal) {
					break;
				}
			}
		}
		return retVal;
	}

	static QString makeVariable(QString name) {
		// TODO: Should we complain if the string is already a variable?

		name.prepend('%');
		name.append('%');

		return name;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class duParameterBase : public qbuPropertyMap, public duVarName {
	Q_OBJECT
public:
	enum DicomNullBehavior {
		NB_WARN    = 0,
		NB_IGNORE  = 1,
		NB_DELETE  = 2,
		NB_DEFAULT = NB_WARN,
	};

public:
	bool           setDisplayName(QString strDisplayName);
	bool           setValue(QVariant vtValue);
	bool           getValue(QVariant& vtValue);
	bool           getValue(QString& strValue, bool bUseFormat = true, bool bVaildate = true);
	bool           setDefaultValue(QVariant vtValue);
	bool           getDefaultValue(QString& strValue);
	bool           getDicomNullBehavior(DicomNullBehavior& dn);
	virtual bool   setValueToDefault();
	virtual bool   setVariableValue(QString strVarName, QString strVal);
	bool           hasFormat();

	static QString nullValue();

protected:
	virtual bool validate() {
		return true;
	}
	virtual QString formatValue(QString strValue) {
		return strValue;
	}

signals:
	void valueChanged(duParameterBase* pParam);
	void validation_failed(duParameterBase* pParam);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(duParameterBase);
Q_DECLARE_METATYPE(duParameterBase*);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // DUPARAMETERBASE_H
