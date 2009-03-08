#include "UserPropPtr.h"
#include "UserPropery.h"
#include "PropXMLHelper.h"
#include "Property.h"

/////////////////////////////////////////////////////////////////////////////////////////

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	class UserPropPtrXMLHelper : public UserPropXMLHelper
	{
	public:
		UserPropPtrXMLHelper(const char* className);
	public:
		virtual bool fromXML(Property* pProp,QDomElement & domElem);
	};

/////////////////////////////////////////////////////////////////////////////////////////

	UserPropPtrXMLHelper::UserPropPtrXMLHelper(const char* className) : UserPropXMLHelper(className)
	{
		PropXMLHelper* pPropXMLHelper = PropXMLHelper::instance();
		if (pPropXMLHelper != NULL) {
			pPropXMLHelper->addHelper(this);
		}	
	}

/////////////////////////////////////////////////////////////////////////////////////////

	bool UserPropPtrXMLHelper::fromXML(Property* pProp,QDomElement & docElem)
	{
		bool retVal = (pProp != NULL);
	
		QDomNode n =docElem.firstChild();
		retVal = !n.isNull();
		if (retVal) {
			QDomElement e = n.toElement();
			retVal = !e.isNull();
			if (retVal) {
				QString strTypeName = e.attribute("tyName");

				UserPropXMLHelper* pHlpr = PropXMLHelper::instance()->GetXMLHelper(strTypeName);


				retVal = (pHlpr != NULL);
			
				if (retVal) {
					UserProperty* pUserProp = pHlpr->construct();
					retVal = (pUserProp != NULL);
					if (retVal) {
						QDomNode n = e.firstChild();

						retVal = !n.isNull();

						if (retVal) {
							QDomElement e = n.toElement();
							retVal = !e.isNull();
							if (retVal) {
								pUserProp->fromXML(e);
								pProp->SetData(UserPropPtr(pUserProp));

								pProp->setObjectName(docElem.tagName());
							}
						}
					}
				}
			}
			
		}


		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	static int m_nMetaID = qRegisterMetaType<QTUTILS::UserPropPtr>();

	UserPropPtrXMLHelper hlpr(QMetaType::typeName(m_nMetaID));


/////////////////////////////////////////////////////////////////////////////////////////

UserPropPtr::UserPropPtr() : m_pProp(NULL)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

UserPropPtr::UserPropPtr(UserProperty* pProp) : m_pProp(pProp)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

UserPropPtr::UserPropPtr( const UserPropPtr & other ) 
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

void UserPropPtr::copy( const UserPropPtr & other )
{
	m_pProp = other.m_pProp;
}

/////////////////////////////////////////////////////////////////////////////////////////

void UserPropPtr::destroy()
{
	// The shared pointer should handle this.
}

/////////////////////////////////////////////////////////////////////////////////////////

bool UserPropPtr::isNull()
{
	return !m_pProp;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString UserPropPtr::toXML( bool bMakeRoot /*= true*/ )
{
	QString retVal;
	if (!isNull()) {
		retVal = m_pProp->toXML(bMakeRoot);
		if (!retVal.isEmpty()) {
			QString strOpen = QString("<UserProp tyName=\"%1\">")
										.arg(typeName());
			
			retVal.prepend(strOpen);

			retVal.append("</UserProp>");

		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

UserProperty* UserPropPtr::data() 
{
	return m_pProp.data();
}

/////////////////////////////////////////////////////////////////////////////////////////

const UserProperty* UserPropPtr::data() const
{
	return m_pProp.data();
}

/////////////////////////////////////////////////////////////////////////////////////////

QString UserPropPtr::typeName() const
{
	QString retVal = data()->metaObject()->className();
	if (!retVal.isEmpty()) {
		retVal.append("*");
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool UserPropPtr::fromXML( QString strXML )
{
	bool retVal;

	QDomDocument doc;
	doc.setContent(strXML);

	QDomElement docElem = doc.documentElement();

	QString strTypeName = docElem.attribute("tyName");

	QDomNode n = docElem.firstChild();

	retVal = !n.isNull();

	if (retVal) {
		QDomElement e = n.toElement();
		retVal = !e.isNull();
		if (retVal) {
			retVal = fromXML(e);
		}
	}

	return retVal;	
}

/////////////////////////////////////////////////////////////////////////////////////////

bool UserPropPtr::fromXML( QDomElement & docElem )
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS