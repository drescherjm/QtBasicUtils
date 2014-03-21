#ifndef __PROPXMLHELPER_H__
#define __PROPXMLHELPER_H__

#include <QMap>
#include <QMutex>
#include <QDomElement>

#include "NonThreadSafeSingleton.h"

namespace QTUTILS {

class Property;
class UserProperty;

/////////////////////////////////////////////////////////////////////////////////////////

struct UserPropXMLHelper 
{
public:
	UserPropXMLHelper(const char* strName);
	UserPropXMLHelper(int nMetaTypeId);
public:
	const char*		GetClassName() const;
protected:
	void	  Initialize();
public:
	virtual bool	fromXML(Property* pProp,QDomElement & domElem);
	virtual UserProperty* construct();
public:
	const char*		m_strClasName;
};

/////////////////////////////////////////////////////////////////////////////////////////

class PropXMLHelper : public NonThreadSafeSingleton<PropXMLHelper>
{
public:
	bool addHelper(UserPropXMLHelper* pHlpr);
	UserPropXMLHelper* GetXMLHelper(QString strClassName);

	typedef QMap<QString,UserPropXMLHelper*> MapHelpers;
private:
	MapHelpers	m_mapHelpers;
	QMutex		m_mutex;
};

/////////////////////////////////////////////////////////////////////////////////////////

template<class T>
class UserPropPtrHelper : public UserPropXMLHelper
{
public:
	UserPropPtrHelper(const char* strName);
	UserPropPtrHelper(int nMetaTypeID);
public:
	virtual UserProperty* construct();
};

/////////////////////////////////////////////////////////////////////////////////////////

template<class T>
UserPropPtrHelper<T>::UserPropPtrHelper(const char* strName) : UserPropXMLHelper(strName)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////

template<class T>
UserPropPtrHelper<T>::UserPropPtrHelper(int nMetaTypeID) : UserPropXMLHelper(nMetaTypeID)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template<class T>
UserProperty* UserPropPtrHelper<T>::construct()
{
	return new T;
}

/////////////////////////////////////////////////////////////////////////////////////////

};// namespace QTUTILS

#endif //__PROPXMLHELPER_H__
