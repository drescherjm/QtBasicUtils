#include "qbuBase/qbuProperyMapXMLHelper.h"
#include "qbuBase/qbuPropertyMap.h"
/////////////////////////////////////////////////////////////////////////////////////////

qbuProperyMapXMLHelper::qbuProperyMapXMLHelper(int nMetaTypeID) : qbuUserPropXMLHelper(nMetaTypeID)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuProperyMapXMLHelper::fromXML(qbuProperty* pProp,QDomElement & docElem)
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
