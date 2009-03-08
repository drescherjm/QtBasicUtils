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
public:
	const char*		GetClassName() const;
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


};// namespace QTUTILS

#endif //__PROPXMLHELPER_H__