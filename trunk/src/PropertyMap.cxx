#include "PropertyMap.h"
#include "PropXMLHelper.h"

#include <QDomDocument>
#include <QTextStream>
#include <QFile>
#include <iostream>

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

class ProperyMapXMLHelper : public UserPropXMLHelper
{
public:
	ProperyMapXMLHelper(const char* className);
public:
	virtual bool fromXML(Property* pProp,QDomElement & domElem);
};

/////////////////////////////////////////////////////////////////////////////////////////

ProperyMapXMLHelper::ProperyMapXMLHelper(const char* className) : UserPropXMLHelper(className)
{
	PropXMLHelper* pPropXMLHelper = PropXMLHelper::instance();
	if (pPropXMLHelper != NULL) {
		pPropXMLHelper->addHelper(this);
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////

bool ProperyMapXMLHelper::fromXML(Property* pProp,QDomElement & docElem)
{
	bool retVal = (pProp != NULL);
	if (retVal) {
		PropertyMap pm;
	
		QDomNode n = docElem.firstChild();

		retVal = !n.isNull();

		if (retVal) {
			QDomElement e = n.toElement();
			retVal = !e.isNull();
			if (retVal) {
				pm.fromXML(e);
				pProp->SetData(QVariant::fromValue<PropertyMap>(pm));
				pProp->setObjectName(docElem.tagName());
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

class ProperyMapPtrXMLHelper : public UserPropXMLHelper
{
public:
	ProperyMapPtrXMLHelper(const char* className);
public:
	virtual UserProperty* construct();
};

/////////////////////////////////////////////////////////////////////////////////////////

ProperyMapPtrXMLHelper::ProperyMapPtrXMLHelper(const char* className) : UserPropXMLHelper(className)
{
	PropXMLHelper* pPropXMLHelper = PropXMLHelper::instance();
	if (pPropXMLHelper != NULL) {
		pPropXMLHelper->addHelper(this);
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////

UserProperty* ProperyMapPtrXMLHelper::construct()
{
	return new PropertyMap;
}

/////////////////////////////////////////////////////////////////////////////////////////

static int m_nMetaID = qRegisterMetaType<QTUTILS::PropertyMap>();
static int m_nMetaIDPtr = qRegisterMetaType<QTUTILS::PropertyMap*>();

ProperyMapXMLHelper hlpr(QMetaType::typeName(m_nMetaID));
ProperyMapPtrXMLHelper ptrHlpr(QMetaType::typeName(m_nMetaIDPtr));

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
		pProp->setObjectName(strName);

		// Remove the old if found otherwise there would be a memory leak.
		RemoveProperty(strName); 

		retVal = m_mapProps.insert(strName,pProp);
		if (retVal != m_mapProps.end()) {
			Modify();
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////
// The bMakeRoot will be used in the case that the PropertyMap is the root node in xml.
// without this param an xml file of a ProperyMap would be invalid because each child 
// would be considered a root node. If there is no root the fromXML would only import
// the first child. Set this to false if the PropertyMap is not the root and is instead
// embedded inside a Property.

QString PropertyMap::toXML( bool bMakeRoot /*= true*/ )
{
	QString name = objectName();

	if (name.isEmpty()) {
		name = "doc";
	}
	
	QVariant::Type ty = QVariant::UserType;

	QString retVal;
	
	if (bMakeRoot) {
		retVal= QString("<%1 ty=\"%2\">\n")
			.arg(name)
			.arg(ty);
	}

	iterator it = begin();
	
	for (;it != end();++it) {
		retVal += (*it)->toXML();
	}

	if (bMakeRoot) {
		retVal += QString("</%1>\n").arg(name);
	}
	
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

	strName.replace(" ","_");
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

//This is just for debugging
#if 0

static void printDomElem(QDomElement & e)
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

	std::cout << e.prefix().toStdString() << std::endl;

		QString str;
			QTextStream stream(&str);

				e.save(stream,0);
					
				std::cout << str.toStdString() << std::endl;
				std::cout << "Parse End." << std::endl << std::endl;
}
#endif //0


/////////////////////////////////////////////////////////////////////////////////////////

bool PropertyMap::fromXML( QString strXML )
{
	bool retVal;

	QDomDocument doc;
	doc.setContent(strXML);

	QDomElement docElem = doc.documentElement();

	QDomNode n = docElem.firstChild();

	retVal = !n.isNull();

	if (retVal) {
		QDomElement e = n.toElement();
		retVal = !e.isNull();
		if (retVal) {
			retVal = fromXML(e);
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool PropertyMap::fromXML(QDomElement & domElem)
{
	bool retVal;
	QDomNode n = domElem;
	retVal = !n.isNull();

	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()) {
			
			Property prop;
			if (prop.fromXML(e)) {
				insert(prop);
			}

		}

		n = n.nextSibling();
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool PropertyMap::Load( QString strFile )
{
	QFile file(strFile);
	bool retVal = file.open(QFile::ReadOnly|QFile::Text);
	if (retVal) {
		QString strXML;
		QTextStream stream(&file);
		strXML = stream.readAll();

		retVal = fromXML(strXML);
		if (retVal) {
			ForceUnmodified();
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool PropertyMap::Save( QString strFile )
{
	QString strXML = toXML(true);
	bool retVal = !strXML.isEmpty();
	if (retVal) {
		QFile file(strFile);
		retVal = file.open(QFile::WriteOnly|QFile::Text|QFile::Truncate);
		if (retVal) {
			QTextStream stream(&file);
			stream << strXML;
			ForceUnmodified();
		}
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS