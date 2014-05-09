#include "qbuBase/qbuPropertyMap.h"
#include "qbuBase/qbuPropXMLHelper.h"

#include <QDomDocument>
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <QStringList>
#include <QSet>
#include "qbuBase/qbuProperyMapXMLHelper.h"
#include <QXmlSimpleReader>
#include <QDebug>

/////////////////////////////////////////////////////////////////////////////////////////

static int m_nMetaID = qRegisterMetaType<qbuPropertyMap>();
static qbuProperyMapXMLHelper hlpr(m_nMetaID);

static int m_nMetaIDPtr = qRegisterMetaType<qbuPropertyMap*>();
qbuUserPropPtrHelper<qbuPropertyMap> ptrHlpr(m_nMetaIDPtr);

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::qbuPropertyMap() : m_cs(Qt::CaseInsensitive)
{
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::~qbuPropertyMap()
{
	destroy();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::qbuPropertyMap(const qbuPropertyMap & other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap& qbuPropertyMap::operator =(const qbuPropertyMap & other)
{
	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyMap::copy(const qbuPropertyMap & other)
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

void qbuPropertyMap::destroy()
{
	iterator it= begin();
	for(; it != end();++it) {
		delete *it;
	}
	m_mapProps.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::iterator qbuPropertyMap::begin() 
{
	qbuPropertyMap::iterator retVal = m_mapProps.begin();
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::iterator qbuPropertyMap::end() 
{
	qbuPropertyMap::iterator retVal = m_mapProps.end();
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::const_iterator qbuPropertyMap::begin() const
{
	qbuPropertyMap::const_iterator retVal = m_mapProps.begin();
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::const_iterator qbuPropertyMap::end() const
{
	qbuPropertyMap::const_iterator retVal = m_mapProps.end();
	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::iterator qbuPropertyMap::insert(qbuProperty & prop)
{
	return insert(new qbuProperty(prop));
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *  \brief This member inserts a Property that is allocated on the heap.
 *
 *	\warning Do not pass this a pointer to a stack allocated Property.
 */

qbuPropertyMap::iterator qbuPropertyMap::insert(qbuProperty* pProp)
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
			propertyInserted(pProp);
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

QString qbuPropertyMap::toXML( bool bMakeRoot /*= true*/, qbuITKIndent indent )
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

	indent = indent.GetNextIndent();

	iterator it = begin();
	
	for (;it != end();++it) {
		retVal += (*it)->toXML(indent);
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

QString qbuPropertyMap::CleanUpName( QString strName ) const
{
	strName = strName.simplified();

	strName.replace(" ","_");
	if (m_cs == Qt::CaseInsensitive) {
		strName = strName.toUpper();
	}

	return strName;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::iterator qbuPropertyMap::find( QString strName ) 
{
	strName = CleanUpName(strName);
	qbuPropertyMap::iterator retVal = m_mapProps.find(strName);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyMap::const_iterator qbuPropertyMap::find( QString strName ) const
{
	strName = CleanUpName(strName);
	qbuPropertyMap::const_iterator retVal = m_mapProps.find(strName);
	return retVal;
}


/////////////////////////////////////////////////////////////////////////////////////////


void qbuPropertyMap::setCaseSensitivity(Qt::CaseSensitivity cs )
{
	if (m_mapProps.isEmpty()) {
		m_cs = cs;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyMap::CopyProperty( QString strOldName, const qbuPropertyMap & other, QString strNewName/*=""*/ )
{
	
	if (strNewName.isEmpty()) {
		strNewName = strOldName;
	}

	qbuPropertyMap::const_iterator it = other.find(strOldName);
	if ( it != other.end()) {
		qbuProperty prop = **it;
		
		if (!strNewName.isEmpty()) {
			prop.setObjectName(strNewName);
		}

		insert(prop);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	 This member function moves a property from other to this object.
 */

void qbuPropertyMap::MoveProperty( QString strOldName, qbuPropertyMap & other, QString strNewName/*=""*/ )
{
	if (strNewName.isEmpty()) {
		strNewName = strOldName;
	}

	qbuPropertyMap::iterator it = other.find(strOldName);
	if ( it != other.end()) {
		qbuProperty prop = **it;

		if (!strNewName.isEmpty()) {
			prop.setObjectName(strNewName);
		}

		insert(prop);

		other.m_mapProps.erase(it);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyMap::RenameProperty(QString strOldName,QString strNewName)
{
	bool retVal = ((!strOldName.isEmpty()) && (!strNewName.isEmpty()));

	if (retVal) {
		iterator it = find(strOldName);

		retVal = (it != end());
		if (retVal) {
			retVal = find(strNewName) == end();
			if (retVal) {
				qbuProperty* pProp = *it;
				m_mapProps.erase(it);
				pProp->setObjectName(strNewName);
				retVal = (insert(pProp) != end());
				if (!retVal) {
					/**
					 *	\warning This should never get here
					 *  \todo Add critical logging	
					 */			
				}
			}
		}

	}
	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyMap::RemoveProperty(QString strName)
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


/**
 *	\brief
 *	This will remove all properties from the lstProperties.
 *	\returns
 *	The number of properties removed.
 */

int qbuPropertyMap::RemoveProperties( QStringList lstProperties )
{
	int retVal = 0;
	iterator it = begin();
	for(; it != end();++it) {
		qbuProperty* pProp = *it;
		if (pProp != NULL) {
			QString strName = pProp->objectName();
			if (lstProperties.contains(strName,Qt::CaseInsensitive)) {
				it = m_mapProps.erase(it);
				retVal++;
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyMap::addProperties(qbuPropertyMap * pOther)
{
	if (pOther != NULL) {
		iterator it = pOther->begin();
		for(;it != pOther->end();++it) {
			insert(**it);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyMap::addProperties( const qbuPropertyMap* other )
{
	qbuPropertyMap::const_iterator it = other->begin();
	if ( it != other->end()) {
		qbuProperty prop = **it;
		insert(prop);
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

QDebug operator<<(QDebug dbg, const QDomNode& node)
{
	QString s;
	QTextStream str(&s, QIODevice::WriteOnly);
	node.save(str, 2);
	dbg << qPrintable(s);
	return dbg;
}


/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyMap::fromXML( QString strXML )
{
	bool retVal;

	QDomDocument doc;
// 	QXmlInputSource source;
// 	source.setData(strXML);
// 	QXmlSimpleReader reader;
// 	doc.setContent(&source, &reader);
		
	doc.setContent(strXML);

	QDomElement docElem = doc.documentElement();

	qDebug() << docElem;

	QDomNode n = docElem.firstChild();

	retVal = !n.isNull();

	if (retVal) {

		qDebug() << n;

		QDomElement e = n.toElement();
		retVal = !e.isNull();
		if (retVal) {
			retVal = fromXML(e);
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyMap::fromXML(QDomElement & domElem)
{
	bool retVal;
	QDomNode n = domElem;
	retVal = !n.isNull();

	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()) {
			
			qbuProperty prop;
			if (prop.fromXML(e)) {
				insert(prop);
			}
			else
			{
				retVal = false;
			}

		}

		n = n.nextSibling();
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyMap::Load( QString strFile )
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

bool qbuPropertyMap::Save( QString strFile )
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

void qbuPropertyMap::Print( std::ostream & st, qbuITKIndent indent )
{

	QString strName = metaObject()->className();
	QString strTemp = QString("%1<%2>\n%3%1</%2>\n")
		.arg(indent.getIndent())
		.arg(strName)
		.arg(toXML(false,indent));

	st << qPrintable(strTemp) << std::endl;

}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyMap::Print( QTextStream & st, qbuITKIndent indent )
{

	QString strName = metaObject()->className();
	QString strTemp = QString("%1<%2>\n%3%1</%2>\n")
		.arg(indent.getIndent())
		.arg(strName)
		.arg(toXML(false,indent));

	st << strTemp << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyMap::operator==( const qbuPropertyMap & other ) const
{
	bool retVal = (other.size() == size());
	if (retVal) {
		const_iterator it1 = begin();
		const_iterator it2 = other.begin();
		for(; it1 != end() && it2 != other.end() && retVal;++it1,++it2) {
			qbuProperty* p1 = *it1;
			qbuProperty* p2 = *it2;
			retVal = ((p1 != NULL) && (p2 != NULL) && (*p1 == *p2));
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

int qbuPropertyMap::size() const
{
	return m_mapProps.count();
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This member will test if the subset of Properties given by the list lstPropNames 
 *	have equal values in the other PropertyMap.
 *
 *	\note
 *	The return value will be false if either of the PropertyMaps does not have a 
 *	Property in its collection or the lstPropNames is empty.
 *
 */

bool qbuPropertyMap::EqualSubset( QStringList lstPropNames, const qbuPropertyMap & other )
{
	bool retVal = !lstPropNames.empty();
	if (retVal) {
		qbuProperty prop1,prop2;
		const_iterator it1, it2;
		foreach(QString strName,lstPropNames) {
			it1 = find(strName);
			it2 = other.find(strName);
			retVal = (( it1 != end()) && (it2 != other.end()));
			if (retVal) {
				qbuProperty* p1 = *it1;
				qbuProperty* p2 = *it2;

				retVal = ((p1 != NULL) && (p2 != NULL) && (*p1 == *p2));
			}
			if (!retVal) {
				break;
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyMap::propertyInserted( qbuProperty * pProp )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\brief
 *	This returns the list of all properties currently in the qbuPropertyMap
 */

QStringList qbuPropertyMap::getPropertyList() const
{
	QStringList retVal;
	
	const_iterator it = begin();

	for( ; it != end(); ++it) {
		retVal << it.key();
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyMap::hasField( QString strFieldName ) const
{
	return (find(strFieldName) != end());
}

/////////////////////////////////////////////////////////////////////////////////////////
