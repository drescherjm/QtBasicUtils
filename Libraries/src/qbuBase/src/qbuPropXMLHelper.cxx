#include "qbuBasePCH.h"

#include "qbuBase/qbuPropXMLHelper.h"
#include <QMetaType>

/////////////////////////////////////////////////////////////////////////////////////////

qbuUserPropXMLHelper::qbuUserPropXMLHelper(const char* strName) : m_strClasName(strName)
{
	Initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuUserPropXMLHelper::qbuUserPropXMLHelper( int nMetaTypeId )
{
	m_strClasName = QMetaType::typeName(nMetaTypeId);
	Initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

const char* qbuUserPropXMLHelper::GetClassName() const
{
	return m_strClasName;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuUserProperty* qbuUserPropXMLHelper::construct()
{
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUserPropXMLHelper::fromXML(qbuProperty* pProp,QDomElement & domElem)
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuUserPropXMLHelper::fromXML2(qbuProperty* pProp, pugi::xml_node & domElem)
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuUserPropXMLHelper::Initialize()
{
	qbuPropXMLHelper* pPropXMLHelper = qbuPropXMLHelper::instance();
	if (pPropXMLHelper != NULL) {
		pPropXMLHelper->addHelper(this);
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuUserPropXMLHelper* qbuPropXMLHelper::GetXMLHelper(QString strClassName)
{
	qbuUserPropXMLHelper* retVal = NULL;
	QMutexLocker lock(&m_mutex);

	MapHelpers::const_iterator it = m_mapHelpers.find(strClassName);
	if (it != m_mapHelpers.end()) {
		retVal = *it;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropXMLHelper::addHelper(qbuUserPropXMLHelper* pHlpr)
{
	bool retVal = (pHlpr != NULL);
	if (retVal) {

		QString strClassName = pHlpr->GetClassName();

		retVal = !strClassName.isEmpty();

		if (retVal) {
			QMutexLocker lock(&m_mutex);
			MapHelpers::iterator it = m_mapHelpers.find(strClassName);
			retVal = (it == m_mapHelpers.end());
			if (retVal) {
				it = m_mapHelpers.insert(strClassName,pHlpr);
				retVal = (it != m_mapHelpers.end());
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
