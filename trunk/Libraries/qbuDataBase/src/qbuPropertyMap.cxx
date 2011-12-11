#include "smBasePCH.h"
#include "smPropertyMap.h"

/////////////////////////////////////////////////////////////////////////////////////////

bool smPropertyMap::hasField( QString strFieldName ) const
{
	return (find(strFieldName) != end());
}

/////////////////////////////////////////////////////////////////////////////////////////

bool smPropertyMap::operator==( const smPropertyMap & other ) const
{
	return Superclass::operator ==(other);
}