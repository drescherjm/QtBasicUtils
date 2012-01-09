#include "PropertyList.h"
#include "PropXMLHelper.h"

#include <QDomDocument>
#include <QTextStream>
#include <QFile>
#include <iostream>

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////
// The following is needed so that the UserPropPtr class can create objects of types it 
// knows about. This registers PropertyList with PropXMLHelper which will call 
// hlpr->construct() to do the actual object construction.

int PropertyList::m_nMetaID = qRegisterMetaType<QTUTILS::PropertyList*>();
static UserPropPtrHelper<PropertyList> hlpr(PropertyList::m_nMetaID);

/////////////////////////////////////////////////////////////////////////////////////////

	PropertyList::PropertyList() 
	{
	}

/////////////////////////////////////////////////////////////////////////////////////////

	PropertyList::~PropertyList()
	{
		destroy();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	PropertyList::PropertyList(const PropertyList & other)
	{
		copy(other);
	}

/////////////////////////////////////////////////////////////////////////////////////////

	PropertyList& PropertyList::operator =(const PropertyList & other)
	{
		if ( &other != this ) {
			destroy();
			copy(other);
		}
		return (*this);
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void PropertyList::copy(const PropertyList & other)
	{
		setObjectName(other.objectName());
		
		List list = other.m_lstProps;

		iterator it= list.begin();
		for(; it != list.end();++it) {
			push_back(**it);
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void PropertyList::destroy()
	{
		iterator it= begin();
		for(; it != end();++it) {
			delete *it;
		}
		m_lstProps.clear();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	PropertyList::iterator PropertyList::begin()
	{
		PropertyList::iterator retVal = m_lstProps.begin();
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	PropertyList::iterator PropertyList::end()
	{
		return m_lstProps.end();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	PropertyList::const_iterator PropertyList::begin() const
	{
		return m_lstProps.begin();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	PropertyList::const_iterator PropertyList::end() const
	{
		return m_lstProps.end();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void PropertyList::push_back(Property & prop)
	{
		return push_back(new Property(prop));
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void PropertyList::push_back(Property* pProp)
	{
		if (pProp != NULL) {
			QString strName = CleanUpName(pProp->objectName());
			pProp->setObjectName(strName);

			m_lstProps.push_back(pProp);
			Modify();
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void PropertyList::push_front(Property & prop)
	{
		return push_front(new Property(prop));
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void PropertyList::push_front(Property* pProp)
	{
		if (pProp != NULL) {
			QString strName = CleanUpName(pProp->objectName());
			pProp->setObjectName(strName);

			m_lstProps.push_front(pProp);
			Modify();
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////
// The bMakeRoot will be used in the case that the PropertyList is the root node in xml.
// without this param an xml file of a ProperyMap would be invalid because each child 
// would be considered a root node. If there is no root the fromXML would only import
// the first child. Set this to false if the PropertyList is not the root and is instead
// embedded inside a Property.

	QString PropertyList::toXML( bool bMakeRoot /*= true*/,qbuITKIndent indent )
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

	QString PropertyList::CleanUpName(QString strName)
	{
		strName = strName.simplified();

		strName.replace(" ","_");
		
		return strName;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void PropertyList::push_back(PropertyList * pOther)
	{
		if (pOther != NULL) {
			iterator it = pOther->begin();
			for(;it != pOther->end();++it) {
				push_back(**it);
			}
		}
	}

/////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////

	bool PropertyList::fromXML( QString strXML )
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

	bool PropertyList::fromXML(QDomElement & domElem)
	{
		bool retVal;
		QDomNode n = domElem;
		retVal = !n.isNull();

		while(!n.isNull()) {
			QDomElement e = n.toElement(); // try to convert the node to an element.
			if(!e.isNull()) {

				Property prop;
				if (prop.fromXML(e)) {
					push_back(prop);
				}

			}

			n = n.nextSibling();
		}

		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	bool PropertyList::Load( QString strFile )
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

	bool PropertyList::Save( QString strFile )
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

	int PropertyList::size() const
	{
		return m_lstProps.size();
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void PropertyList::Print( std::ostream & st,qbuITKIndent indent )
	{
		QString str = toXML(true,indent);
		st << qPrintable(str) << std::endl;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	
	bool PropertyList::operator==( const PropertyList & other ) const
	{
		bool retVal = (other.size() == size());
		if (retVal) {
			const_iterator it1 = begin();
			const_iterator it2 = other.begin();
			for(; it1 != end() && it2 != other.end() && retVal;++it1,++it2) {
				Property* p1 = *it1;
				Property* p2 = *it2;
				retVal = ((p1 != NULL) && (p2 != NULL) && (*p1 == *p2));
			}
		}
		return retVal;
	}

}; // namespace QTUTILS
