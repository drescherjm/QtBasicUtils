#include "qbuBasePCH.h"

#include "qbuBase/qbuPropertyTypeNameAlias.h"

/////////////////////////////////////////////////////////////////////////////////////////

QString qbuPropertyTypeNameAlias::getAlias( QString strClassTypeName )
{
	QString retVal = strClassTypeName;

	QMutexLocker lock(&m_mutex);
	
	MapAliases::const_iterator it = m_mapHelpers.find(strClassTypeName);
	if (it != m_mapHelpers.end()) {
		retVal = *it;
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyTypeNameAlias::addAlias( QString strClassTypeName, QString strTypeNameAlias )
{
	bool retVal = !strClassTypeName.isEmpty();
	if (retVal) {
		m_mapHelpers.insert(strClassTypeName,strTypeNameAlias);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
