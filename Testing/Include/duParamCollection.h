#pragma once
#ifndef DUPARAMCOLLECTION_H
#define DUPARAMCOLLECTION_H

/////////////////////////////////////////////////////////////////////////////////////////

#include "qbuBase/qbuPropertyMap.h"

class duParameterBase;

/////////////////////////////////////////////////////////////////////////////////////////

class duParamCollection : public qbuPropertyMap {
	Q_OBJECT
public:
	duParamCollection();
	duParamCollection(const duParamCollection& other);

	using Superclass = qbuPropertyMap;
signals:
	void valueChanged(duParameterBase* pParam);
	void warning(const QString& strMessage);

public:
	iterator insert(duParameterBase* pParam, bool bAutoDelete = true);
	duParameterBase* getParam(duParamCollection::iterator it) const;
	duParameterBase* getParam(duParamCollection::const_iterator it) const;
	void             connectSignals(duParameterBase* pParam);
	template <typename ParamType>
	ParamType* getParamPtr(QString strFieldName) const;
};

/////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename ParamType>
ParamType* duParamCollection::getParamPtr(QString strFieldName) const {
	ParamType*     retVal{nullptr};

	const_iterator it = find(strFieldName);
	if (it != end()) {
		auto pParam = getParam(it);
		retVal      = dynamic_cast<ParamType*>(pParam);
	}
	return retVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(duParamCollection);
Q_DECLARE_METATYPE(duParamCollection*);

#endif // DUPARAMCOLLECTION_H
