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
		UserPropPtrXMLHelper(int nMetaTypeID);
	public:
		virtual bool fromXML(Property* pProp,QDomElement & domElem);
	};

/////////////////////////////////////////////////////////////////////////////////////////

	UserPropPtrXMLHelper::UserPropPtrXMLHelper(int nMetaTypeID) : UserPropXMLHelper(nMetaTypeID)
	{
		
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

	UserPropPtrXMLHelper hlpr(m_nMetaID);


/////////////////////////////////////////////////////////////////////////////////////////

UserPropPtr::UserPropPtr() : m_pPropRaw(NULL)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

UserPropPtr::UserPropPtr(UserProperty* pProp, bool bSmart) 
{
	if (bSmart) {
		m_pProp = pProp;
		m_pPropRaw = NULL;
	}
	else
	{
		m_pProp.reset();
		m_pPropRaw = pProp;
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////

UserPropPtr::UserPropPtr( const UserPropPtr & other ) 
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

UserPropPtr::UserPropPtr(SharedPtr & other)
{
	m_pProp = other;
}

/////////////////////////////////////////////////////////////////////////////////////////

void UserPropPtr::copy( const UserPropPtr & other )
{
	m_pProp = other.m_pProp;
	m_pPropRaw = other.m_pPropRaw;
}

/////////////////////////////////////////////////////////////////////////////////////////

void UserPropPtr::destroy()
{
	// The shared pointer should handle this.
}

/////////////////////////////////////////////////////////////////////////////////////////

bool UserPropPtr::isNull() const
{
	return (!m_pProp && (m_pPropRaw == NULL));
}

/////////////////////////////////////////////////////////////////////////////////////////

QString UserPropPtr::toXML( bool bMakeRoot /*= true*/ )
{
	QString retVal;
	if (!isNull()) {
		retVal = data()->toXML(bMakeRoot);
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
	return willAutoDelete() ? m_pProp.data() : m_pPropRaw;
}

/////////////////////////////////////////////////////////////////////////////////////////

const UserProperty* UserPropPtr::data() const
{
	return willAutoDelete() ? m_pProp.data() : m_pPropRaw;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool UserPropPtr::willAutoDelete() const
{
	return (m_pPropRaw == NULL);
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

UserPropPtr::SharedPtr UserPropPtr::GetPtr()
{
	return m_pProp;
}

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS
