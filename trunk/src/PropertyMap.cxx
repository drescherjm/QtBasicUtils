#include "PropertyMap.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

PropertyMap::PropertyMap() : m_cs(Qt::CaseInsensitive)
{
}

/////////////////////////////////////////////////////////////////////////////////////////

PropertyMap::~PropertyMap()
{
	destroy();
}

/////////////////////////////////////////////////////////////////////////////////////////

PropertyMap::PropertyMap(const PropertyMap & other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

PropertyMap& PropertyMap::operator =(const PropertyMap & other)
{
	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

void PropertyMap::copy(const PropertyMap & other)
{
	setObjectName(other.objectName());
	setCaseSensitivity(other.m_cs);

	Map map = other.m_mapProps;
	
	iterator it= map.begin();
	for(; it != map.end();++it) {
		insert(**it);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void PropertyMap::destroy()
{
	iterator it= begin();
	for(; it != end();++it) {
		delete *it;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

PropertyMap::iterator PropertyMap::begin()
{
	return m_mapProps.begin();
}

/////////////////////////////////////////////////////////////////////////////////////////

PropertyMap::iterator PropertyMap::end()
{
	return m_mapProps.end();
}

/////////////////////////////////////////////////////////////////////////////////////////

PropertyMap::iterator PropertyMap::insert(Property & prop)
{
	return insert(new Property(prop));
}

/////////////////////////////////////////////////////////////////////////////////////////

PropertyMap::iterator PropertyMap::insert(Property* pProp)
{
	iterator retVal = m_mapProps.end();
	if (pProp != NULL) {
		QString strName = CleanUpName(pProp->objectName());
		retVal = m_mapProps.insert(strName,pProp);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////
//
// This cleans up whitespace and applies the case sensitivity.
//
/////////////////////////////////////////////////////////////////////////////////////////

QString PropertyMap::CleanUpName(QString strName)
{
	strName = strName.simplified();
	if (m_cs == Qt::CaseInsensitive) {
		strName = strName.toUpper();
	}

	return strName;
}

/////////////////////////////////////////////////////////////////////////////////////////

PropertyMap::iterator PropertyMap::find(QString strName)
{
	strName = CleanUpName(strName);
	return m_mapProps.find(strName);
}

/////////////////////////////////////////////////////////////////////////////////////////


void PropertyMap::setCaseSensitivity(Qt::CaseSensitivity cs )
{
	if (m_mapProps.isEmpty()) {
		m_cs = cs;
	}
}

}; // namespace QTUTILS