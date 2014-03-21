#include "ProperyMapXMLHelper.h"
#include "PropertyMap.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

ProperyMapXMLHelper::ProperyMapXMLHelper(int nMetaTypeID) : UserPropXMLHelper(nMetaTypeID)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool ProperyMapXMLHelper::fromXML(Property* pProp,QDomElement & docElem)
{
	bool retVal = (pProp != NULL);
	if (retVal) {
		PropertyMap pm;
	
		QDomNode n = docElem.firstChild();

		retVal = !n.isNull();

		if (retVal) {
			QDomElement e = n.toElement();
			retVal = !e.isNull();
			if (retVal) {
				pm.fromXML(e);
				pProp->SetData(QVariant::fromValue<PropertyMap>(pm));
				pProp->setObjectName(docElem.tagName());
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS