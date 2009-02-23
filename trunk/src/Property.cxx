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

QString	Property::toXML()
{
	QString retVal;
	QVariant::Type ty = GetData().type();

	if (ty < QVariant::UserType) {
		QString strName = objectName();
		retVal = GetData().toString();
		QString strTemp = QString("<%1 ty=\"%2\">%3</%1>\n")
			.arg(strName)
			.arg(ty)
			.arg(retVal);
		retVal = strTemp;
	}
	return retVal;

}

}; // namespace QTUTILS