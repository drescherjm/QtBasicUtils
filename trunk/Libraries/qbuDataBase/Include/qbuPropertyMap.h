#ifndef __SMPROPERTYMAP_H__
#define __SMPROPERTYMAP_H__

#include "PropertyMap.h"
#include "smMacros.h"


/**
*	
*	\ingroup smBase
*/

class smPropertyMap : public QTUTILS::PropertyMap
{
	SM_DECLARE_SUPERCLASS(QTUTILS::PropertyMap);
public:
	bool	operator==(const smPropertyMap & other) const;
public:
	bool	hasField(QString strFieldName) const;
public:
	template<typename DataType>
	bool	getField(QString strFieldName, DataType & nOutVal);
	template<typename DataType>
	bool	setField(QString strFieldName, DataType nInVal);
};

/////////////////////////////////////////////////////////////////////////////////////////

template<typename DataType>
bool smPropertyMap::getField( QString strFieldName, DataType & nOutVal )
{
	bool retVal;
	const_iterator it = find(strFieldName);
	retVal = (it != end());
	if (retVal) {
		QTUTILS::Property* pProp =*it;
		QVariant vt = (*it)->GetData();
		retVal = vt.canConvert<DataType>();
		nOutVal = vt.value<DataType>();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

template<typename DataType>
bool smPropertyMap::setField( QString strFieldName, DataType nInVal )
{
	bool retVal;
	QTUTILS::Property prop;
	prop.setObjectName(strFieldName);
	prop.SetData(nInVal);
	retVal = (insert(prop) != end());
	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

#endif //__SMPROPERTYMAP_H__
