#include "Property.h"

namespace QTUTILS {

Property::Property()
{
}

Property::~Property()
{
	destroy();
}

Property::Property(const Property & other)
{
	copy(other);
}

Property& Property::operator =(const Property & other)
{
	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

void Property::copy(const Property & other)
{
	m_vt = other.m_vt;
	setObjectName(other.objectName());
}

void Property::destroy()
{

}

QVariant& Property::GetData()
{
	return m_vt;
}

}; // namespace QTUTILS