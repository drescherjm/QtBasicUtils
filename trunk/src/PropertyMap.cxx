#include "PropertyMap.h"

namespace QTUTILS {

PropertyMap::PropertyMap()
{
}

PropertyMap::~PropertyMap()
{
	destroy();
}

PropertyMap::PropertyMap(const PropertyMap & other)
{
	copy(other);
}

PropertyMap& PropertyMap::operator =(const PropertyMap & other)
{
	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

void PropertyMap::copy(const PropertyMap & other)
{
	setObjectName(other.objectName());

	Map map = other.m_mapProps;
	
	iterator it= map.begin();
	for(; it != map.end();++it) {
		insert(**it);
	}
}

void PropertyMap::destroy()
{
	iterator it= begin();
	for(; it != end();++it) {
		delete *it;
	}
}

PropertyMap::iterator PropertyMap::begin()
{
	return m_mapProps.begin();
}

PropertyMap::iterator PropertyMap::end()
{
	return m_mapProps.end();
}


PropertyMap::iterator PropertyMap::insert(Property & prop)
{
	return insert(new Property(prop));
}

PropertyMap::iterator PropertyMap::insert(Property* pProp)
{
	iterator retVal = m_mapProps.end();
	if (pProp != NULL) {
		retVal = m_mapProps.insert(pProp->objectName(),pProp);
	}
	return retVal;
}

QString PropertyMap::toXML()
{
	QString name = objectName();
	
	QVariant::Type ty = QVariant::UserType;

	QString retVal;
		
		
	/*= QString("<%1 ty=\"%2\">\n")
			.arg(name)
			.arg(ty);
	*/

	iterator it = begin();
	
	for (;it != end();++it) {
		retVal += (*it)->toXML();
	}

	//retVal += QString("</%1>\n").arg(name);

	return retVal;
}

}; // namespace QTUTILS