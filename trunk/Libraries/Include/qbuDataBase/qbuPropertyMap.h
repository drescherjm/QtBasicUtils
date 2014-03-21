#include "qbuBase/PropertyMap.h"
#include "qbuMacros.h"


/**
*	
*	\ingroup smBase
*/

class qbuPropertyMap : public PropertyMap
{
	QBU_DECLARE_SUPERCLASS(PropertyMap);
public:
	bool	operator==(const qbuPropertyMap & other) const;
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
bool qbuPropertyMap::getField( QString strFieldName, DataType & nOutVal )
{
	bool retVal;
	const_iterator it = find(strFieldName);
	retVal = (it != end());
	if (retVal) {
		Property* pProp =*it;
		QVariant vt = (*it)->GetData();
		retVal = vt.canConvert<DataType>();
		nOutVal = vt.value<DataType>();
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

template<typename DataType>
bool qbuPropertyMap::setField( QString strFieldName, DataType nInVal )
{
	bool retVal;
	Property prop;
	prop.setObjectName(strFieldName);
	prop.SetData(nInVal);
	retVal = (insert(prop) != end());
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

