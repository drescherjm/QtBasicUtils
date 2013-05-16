#ifndef __PROPERYMAPXMLHELPER_H__
#define __PROPERYMAPXMLHELPER_H__

#include "PropXMLHelper.h"
#include "Property.h"
#include <QDomElement>

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

class ProperyMapXMLHelper : public UserPropXMLHelper
{
public:
	ProperyMapXMLHelper(int nMetaTypeID);
public:
	virtual bool fromXML(Property* pProp,QDomElement & domElem);
};

/////////////////////////////////////////////////////////////////////////////////////////


}; // namespace QTUTILS

#endif __PROPERYMAPXMLHELPER_H__