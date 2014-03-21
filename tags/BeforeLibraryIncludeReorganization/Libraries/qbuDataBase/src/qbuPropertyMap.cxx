#include "qbuPropertyMap.h"

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyMap::hasField( QString strFieldName ) const
{
	return (find(strFieldName) != end());
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyMap::operator==( const qbuPropertyMap & other ) const
{
	return Superclass::operator ==(other);
}