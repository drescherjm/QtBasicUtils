#include "qbuBasePCH.h"

#include "qbuBase/qbuUserPropPtr.h"
#include "qbuBase/qbuUserPropery.h"
#include "qbuBase/qbuPropXMLHelper.h"
#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuPropertyTypeNameAlias.h"

#define USERPROPPTRTYPENAME "QTUTILS::UserPropPtr"

/////////////////////////////////////////////////////////////////////////////////////////

class UserPropPtrXMLHelper : public qbuUserPropXMLHelper
{
public:
	UserPropPtrXMLHelper(int nMetaTypeID);
public:
	virtual bool fromXML(qbuProperty* pProp,QDomElement & domElem);
};

/////////////////////////////////////////////////////////////////////////////////////////

UserPropPtrXMLHelper::UserPropPtrXMLHelper(int nMetaTypeID) : qbuUserPropXMLHelper(USERPROPPTRTYPENAME)
{
	qbuPropertyTypeNameAlias::instance()->addAlias(QMetaType::typeName(nMetaTypeID),USERPROPPTRTYPENAME);
}

/////////////////////////////////////////////////////////////////////////////////////////

bool UserPropPtrXMLHelper::fromXML(qbuProperty* pProp,QDomElement & docElem)
{
	bool retVal = (pProp != NULL);

	QDomNode n =docElem.firstChild();
	retVal = !n.isNull();
	if (retVal) {
		QDomElement e = n.toElement();
		retVal = !e.isNull();
		if (retVal) {
			QString strTypeName = e.attribute("tyName");

			qbuUserPropXMLHelper* pHlpr = qbuPropXMLHelper::instance()->GetXMLHelper(strTypeName);

			retVal = (pHlpr != NULL);

			if (retVal) {
				qbuUserProperty* pUserProp = pHlpr->construct();
				retVal = (pUserProp != NULL);
				if (retVal) {
					QDomNode n = e.firstChild();

					retVal = !n.isNull();

					if (retVal) {
						QDomElement e = n.toElement();
						retVal = !e.isNull();
						if (retVal) {
							pUserProp->fromXML(e);
							pProp->SetData(qbuUserPropPtr(pUserProp));

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

static int m_nMetaID = qRegisterMetaType<qbuUserPropPtr>();

UserPropPtrXMLHelper hlpr(m_nMetaID);


/////////////////////////////////////////////////////////////////////////////////////////

qbuUserPropPtr::qbuUserPropPtr() : m_pPropRaw(NULL)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

qbuUserPropPtr::qbuUserPropPtr(qbuUserProperty* pProp, bool bSmart) 
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

qbuUserPropPtr::qbuUserPropPtr( const qbuUserPropPtr & other ) 
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuUserPropPtr::qbuUserPropPtr(SharedPtr & other)
{
	m_pProp = other;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuUserPropPtr& qbuUserPropPtr::operator=(const qbuUserPropPtr& other)
{
	if (&other != this) {
		destroy();
		copy(other);
	}
	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuUserPropPtr::copy( const qbuUserPropPtr & other )
{
	m_pProp = other.m_pProp;
	m_pPropRaw = other.m_pPropRaw;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuUserPropPtr::destroy()
{
	// The shared pointer should handle this.
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUserPropPtr::isNull() const
{
	return (!m_pProp && (m_pPropRaw == NULL));
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuUserPropPtr::toXML( bool bMakeRoot /*= true*/, qbuITKIndent indent )
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

qbuUserProperty* qbuUserPropPtr::data() 
{
	return willAutoDelete() ? m_pProp.data() : m_pPropRaw;
}

/////////////////////////////////////////////////////////////////////////////////////////

const qbuUserProperty* qbuUserPropPtr::data() const
{
	return willAutoDelete() ? m_pProp.data() : m_pPropRaw;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUserPropPtr::willAutoDelete() const
{
	return (m_pPropRaw == NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuUserPropPtr::typeName() const
{
	QString retVal = data()->metaObject()->className();
	if (!retVal.isEmpty()) {

		retVal = qbuPropertyTypeNameAlias::instance()->getAlias(retVal);
		retVal.append("*");
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUserPropPtr::fromXML( QString strXML )
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

bool qbuUserPropPtr::fromXML( QDomElement & docElem )
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuUserPropPtr::SharedPtr qbuUserPropPtr::GetPtr()
{
	return m_pProp;
}

/////////////////////////////////////////////////////////////////////////////////////////
