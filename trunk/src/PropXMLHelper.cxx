#include "PropXMLHelper.h"

/////////////////////////////////////////////////////////////////////////////////////////

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	UserPropXMLHelper::UserPropXMLHelper(const char* strName) : m_strClasName(strName)
	{

	}

/////////////////////////////////////////////////////////////////////////////////////////

	const char* UserPropXMLHelper::GetClassName() const
	{
		return m_strClasName;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	UserProperty* UserPropXMLHelper::construct()
	{
		return NULL;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	bool UserPropXMLHelper::fromXML(Property* pProp,QDomElement & domElem)
	{
		return false;
	}

/////////////////////////////////////////////////////////////////////////////////////////

UserPropXMLHelper* PropXMLHelper::GetXMLHelper(QString strClassName)
{
	UserPropXMLHelper* retVal = NULL;
	QMutexLocker lock(&m_mutex);

	MapHelpers::const_iterator it = m_mapHelpers.find(strClassName);
	if (it != m_mapHelpers.end()) {
		retVal = *it;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool PropXMLHelper::addHelper(UserPropXMLHelper* pHlpr)
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

}; // namespace QTUTILS