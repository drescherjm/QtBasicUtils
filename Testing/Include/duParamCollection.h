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
	void connectSignals(duParameterBase* pParam);
};

/////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Q_DECLARE_METATYPE(duParamCollection);
Q_DECLARE_METATYPE(duParamCollection*);

#endif // DUPARAMCOLLECTION_H
