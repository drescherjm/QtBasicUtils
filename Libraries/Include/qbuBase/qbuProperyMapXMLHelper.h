#pragma once

#ifndef __QBUPROPERYMAPXMLHELPER_H__
#define __QBUPROPERYMAPXMLHELPER_H__

#include "qbuBase/qbuPropXMLHelper.h"
#include "qbuBase/qbuProperty.h"

/////////////////////////////////////////////////////////////////////////////////////////

class qbuProperyMapXMLHelper : public qbuUserPropXMLHelper
{
public:
	qbuProperyMapXMLHelper(int nMetaTypeID);
public:
	virtual bool fromXML(qbuProperty* pProp,QDomElement & domElem);
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __QBUPROPERYMAPXMLHELPER_H__
