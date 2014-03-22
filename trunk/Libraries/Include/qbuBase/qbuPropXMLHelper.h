#pragma once

#ifndef __QBUPROPXMLHELPER_H__
#define __QBUPROPXMLHELPER_H__

#include <QMap>
#include <QMutex>
#include <QDomElement>

#include "qbuBase/qbuNonThreadSafeSingleton.h"

class qbuProperty;
class qbuUserProperty;

/////////////////////////////////////////////////////////////////////////////////////////

struct qbuUserPropXMLHelper 
{
public:
	qbuUserPropXMLHelper(const char* strName);
	qbuUserPropXMLHelper(int nMetaTypeId);
public:
	const char*		GetClassName() const;
protected:
	void	  Initialize();
public:
	virtual bool	fromXML(qbuProperty* pProp,QDomElement & domElem);
	virtual qbuUserProperty* construct();
public:
	const char*		m_strClasName;
};

/////////////////////////////////////////////////////////////////////////////////////////

class qbuPropXMLHelper : public NonThreadSafeSingleton<qbuPropXMLHelper>
{
public:
	bool addHelper(qbuUserPropXMLHelper* pHlpr);
	qbuUserPropXMLHelper* GetXMLHelper(QString strClassName);

	typedef QMap<QString,qbuUserPropXMLHelper*> MapHelpers;
private:
	MapHelpers	m_mapHelpers;
	QMutex		m_mutex;
};

/////////////////////////////////////////////////////////////////////////////////////////

template<class T>
class qbuUserPropPtrHelper : public qbuUserPropXMLHelper
{
public:
	qbuUserPropPtrHelper(const char* strName);
	qbuUserPropPtrHelper(int nMetaTypeID);
public:
	virtual qbuUserProperty* construct();
};

/////////////////////////////////////////////////////////////////////////////////////////

template<class T>
qbuUserPropPtrHelper<T>::qbuUserPropPtrHelper(const char* strName) : qbuUserPropXMLHelper(strName)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

template<class T>
qbuUserPropPtrHelper<T>::qbuUserPropPtrHelper(int nMetaTypeID) : qbuUserPropXMLHelper(nMetaTypeID)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template<class T>
qbuUserProperty* qbuUserPropPtrHelper<T>::construct()
{
	return new T;
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __QBUPROPXMLHELPER_H__
