#include "qbuBase/UserPropPtr.h"
#include "qbuBase/UserPropery.h"
#include "qbuBase/PropXMLHelper.h"
#include "qbuBase/Property.h"


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

							QString strName = docElem.tagName();
							pProp->setObjectName(strName);

							if (pUserProp->objectName().isEmpty()) {
								pUserProp->setObjectName(strName);
							}

						}
					}
				}
			}
			else
			{
				std::cerr << "Warning: Could not find a suitable xml helper for the following class: " << 
					qPrintable(strTypeName) << std::endl;
			}
		}

	}


	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

static int m_nMetaID = qRegisterMetaType<UserPropPtr>();

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

QString UserPropPtr::toXML( bool bMakeRoot /*= true*/, qbuITKIndent indent )
{
	QString retVal;
	if (!isNull()) {
		indent = indent.GetNextIndent();
		retVal = data()->toXML(bMakeRoot,indent);
		if (!retVal.isEmpty()) {
			QString strTemp = QString("%1<UserProp tyName=\"%2\">\n%3%1</UserProp>\n")
				.arg(indent.getIndent())
				.arg(typeName())
				.arg(retVal);


			retVal = strTemp;
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
