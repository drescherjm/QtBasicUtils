#include "PropertyMap.h"

#include <QDomDocument>
#include <iostream>

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

/////////////////////////////////////////////////////////////////////////////////////////

void PropertyMap::CopyProperty(QString strName, PropertyMap & other,
							   QString strNewName)
{
	PropertyMap::iterator it = other.find(strName);
	if ( it != other.end()) {
		Property prop = **it;
		
		if (strNewName.isEmpty()) {
			prop.setObjectName(strNewName);
		}

		insert(prop);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

bool PropertyMap::RenameProperty(QString strOldName,QString strNewName)
{
	bool retVal = ((!strOldName.isEmpty()) && (!strNewName.isEmpty()));

	if (retVal) {
		iterator it = find(strOldName);

		retVal = (it != end());
		if (retVal) {
			retVal = find(strNewName) == end();
			if (retVal) {
				Property* pProp = *it;
				m_mapProps.erase(it);
				pProp->setObjectName(strNewName);
				retVal = (insert(pProp) != end());
				if (!retVal) {
					// WARNING: This should never get here
					// TODO: Add critical logging					
				}
			}
		}

	}
	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool PropertyMap::RemoveProperty(QString strName)
{
	bool retVal;
	iterator it = find(strName);
	retVal = (it != end());
	if (retVal) {
		delete *it;
		m_mapProps.erase(it);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void PropertyMap::addProperties(PropertyMap * pOther)
{
	if (pOther != NULL) {
		iterator it = pOther->begin();
		for(;it != pOther->end();++it) {
			insert(**it);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void printDomElem(QDomElement & e)
{
	std::cout << "Parse Begin" << std::endl;
	std::cout << e.tagName().toStdString() << std::endl; // the node really is an element.
	if(e.hasAttribute("tyID")) {
		QString strAttr = e.attribute("tyID");
		if (!strAttr.isEmpty()) {
			std::cout << strAttr.toStdString() << std::endl;
		}
	}
	if(e.hasAttribute("tyName")) {
		QString strAttr = e.attribute("tyName");
		if (!strAttr.isEmpty()) {
			std::cout << strAttr.toStdString() << std::endl;
		}
	}

	std::cout << e.text().toStdString() << std::endl;


	std::cout << "Parse End." << std::endl << std::endl;
}


/////////////////////////////////////////////////////////////////////////////////////////

bool PropertyMap::fromXML( QString strXML )
{
	/*QDomDocument doc;
	bool retVal = doc.setContent(strXML);
	if (retVal) {
		QDomElement docElem = doc.documentElement();
		retVal = !docElem.isNull();
		if (retVal) {
			QString strTypeID = docElem.attribute("tyID");
			retVal = !strTypeID.isEmpty();
			if (retVal) {
				QVariant::Type ty = static_cast<QVariant::Type>(strTypeID.toUInt());
				if ((ty != QVariant::UserType) && (ty != QVariant::Invalid)) {
					m_vt = docElem.text();
					retVal = m_vt.canConvert(ty);
					if (retVal) {
						m_vt.convert(ty);
						setObjectName(docElem.tagName());
					}
				}
			}
		}
	}
	*/

	QDomDocument doc;
	doc.setContent(strXML);
	QDomElement docElem = doc.documentElement();

	printDomElem(docElem);

	QDomNode n = docElem.firstChild();
	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()) {
			printDomElem(e);
		}
		n = n.nextSibling();
	}

	return false;
}

}; // namespace QTUTILS