#include "PropertyCollection.h"

namespace QTUTILS {

PropertyCollection::PropertyCollection()
{
}

PropertyCollection::~PropertyCollection()
{
	destroy();
}

PropertyCollection::PropertyCollection(const PropertyCollection & other)
{
	copy(other);
}

PropertyCollection& PropertyCollection::operator =(const PropertyCollection & other)
{
	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

void PropertyCollection::copy(const PropertyCollection & other)
{
	m_vt = other.m_vt;
	setObjectName(other.objectName());

	PropertyMap map = other.m_mapProps;
	
	iterator it= map.begin();
	for(; it != map.end();++it) {
		insert(**it);
	}
}

void PropertyCollection::destroy()
{
	iterator it= begin();
	for(; it != end();++it) {
		delete *it;
	}
}

PropertyCollection::iterator PropertyCollection::begin()
{
	return m_mapProps.begin();
}

PropertyCollection::iterator PropertyCollection::end()
{
	return m_mapProps.end();
}


PropertyCollection::iterator PropertyCollection::insert(Property & prop)
{
	return insert(new Property(prop));
}

PropertyCollection::iterator PropertyCollection::insert(Property* pProp)
{
	iterator retVal = m_mapProps.end();
	if (pProp != NULL) {
		retVal = m_mapProps.insert(pProp->objectName(),pProp);
	}
	return retVal;
}

}; // namespace QTUTILS