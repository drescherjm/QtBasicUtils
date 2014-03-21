#pragma once

#ifndef __PROPERYMAPXMLHELPER_H__
#define __PROPERYMAPXMLHELPER_H__

#include "PropXMLHelper.h"
#include "qbuBase/Property.h"

/////////////////////////////////////////////////////////////////////////////////////////

class ProperyMapXMLHelper : public UserPropXMLHelper
{
public:
	ProperyMapXMLHelper(int nMetaTypeID);
public:
	virtual bool fromXML(Property* pProp,QDomElement & domElem);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __PROPERYMAPXMLHELPER_H__

