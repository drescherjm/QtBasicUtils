#include "Property.h"
#include "PropertyMap.h"

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
		QString strTemp = QString("<%1 tyID=\"%2\" tyName=\"%3\">%4</%1>\n")
			.arg(strName)
			.arg(ty)
			.arg(GetData().typeName())
			.arg(retVal);
		retVal = strTemp;
	}
	else if (GetData().canConvert<PropertyMap>()) {
		PropertyMap pc = GetData().value<PropertyMap>();
		QString strName = objectName();
		retVal = pc.toXML();

		QString strTemp = QString("<%1 tyID=\"%2\" tyName=\"%3\">\n%4</%1>\n")
			.arg(strName)
			.arg(ty)
			.arg(GetData().typeName())
			.arg(retVal);

		retVal = strTemp;
	}
	return retVal;

}

}; // namespace QTUTILS