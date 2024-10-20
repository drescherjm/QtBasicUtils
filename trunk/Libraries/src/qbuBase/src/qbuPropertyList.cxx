#include "qbuBasePCH.h"

#include "qbuBase/qbuPropertyList.h"
#include "qbuBase/qbuPropXMLHelper.h"



/////////////////////////////////////////////////////////////////////////////////////////
// The following is needed so that the UserPropPtr class can create objects of types it 
// knows about. This registers qbuPropertyList with PropXMLHelper which will call 
// hlpr->construct() to do the actual object construction.

int qbuPropertyList::m_nMetaID = qRegisterMetaType<qbuPropertyList*>();
static qbuUserPropPtrHelper<qbuPropertyList> hlpr(qbuPropertyList::m_nMetaID);

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyList::qbuPropertyList() : m_cs(Qt::CaseInsensitive)
{
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyList::~qbuPropertyList()
{
	destroy();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyList::qbuPropertyList(const qbuPropertyList & other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyList& qbuPropertyList::operator =(const qbuPropertyList & other)
{
	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyList::copy(const qbuPropertyList & other)
{
	setObjectName(other.objectName());
	setCaseSensitivity(other.m_cs);

	List list = other.m_lstProps;

	iterator it= list.begin();
	for(; it != list.end();++it) {
		push_back(**it);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyList::destroy()
{
	iterator it= begin();
	for(; it != end();++it) {
		delete *it;
	}
	m_lstProps.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyList::iterator qbuPropertyList::begin()
{
	qbuPropertyList::iterator retVal = m_lstProps.begin();
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyList::iterator qbuPropertyList::end()
{
	return m_lstProps.end();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyList::iterator qbuPropertyList::find(QString strName)
{
	qbuPropertyList::iterator retVal = begin();
	strName = CleanUpName(strName);
	for (; retVal != end(); ++retVal) {
		qbuProperty* pProp = *retVal;
		const QString& strPropName = pProp->objectName();
		if (strName.compare(strPropName, m_cs) == 0) {
			break;
		}
	}
	
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyList::const_iterator qbuPropertyList::find(QString strName) const
{
	qbuPropertyList::const_iterator retVal = begin();
	strName = CleanUpName(strName);
	for (; retVal != end(); ++retVal) {
		qbuProperty* pProp = *retVal;
		const QString& strPropName = pProp->objectName();
		if (strName.compare(strPropName, m_cs) == 0) {
			break;
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyList::const_iterator qbuPropertyList::begin() const
{
	return m_lstProps.begin();
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuPropertyList::const_iterator qbuPropertyList::end() const
{
	return m_lstProps.end();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyList::setCaseSensitivity(Qt::CaseSensitivity cs)
{
	if (m_lstProps.isEmpty()) {
		m_cs = cs;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyList::push_back(qbuProperty & prop)
{
	return push_back(new qbuProperty(prop));
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyList::push_back(qbuProperty* pProp)
{
	if (pProp != NULL) {
		QString strName = CleanUpName(pProp->objectName());
		pProp->setObjectName(strName);

		m_lstProps.push_back(pProp);
		Modify();
		propertyInserted(pProp);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyList::push_front(qbuProperty & prop)
{
	return push_front(new qbuProperty(prop));
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyList::push_front(qbuProperty* pProp)
{
	if (pProp != NULL) {
		QString strName = CleanUpName(pProp->objectName());
		pProp->setObjectName(strName);

		m_lstProps.push_front(pProp);
		Modify();
		propertyInserted(pProp);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// The bMakeRoot will be used in the case that the qbuPropertyList is the root node in xml.
// without this param an xml file of a ProperyMap would be invalid because each child 
// would be considered a root node. If there is no root the fromXML would only import
// the first child. Set this to false if the qbuPropertyList is not the root and is instead
// embedded inside a qbuProperty.

QString qbuPropertyList::toXML( bool bMakeRoot /*= true*/,qbuITKIndent indent )
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

void qbuPropertyList::propertyInserted(qbuProperty* pProp)
{

}

/////////////////////////////////////////////////////////////////////////////////////////
//
// This cleans up whitespace and applies the case sensitivity.
//
/////////////////////////////////////////////////////////////////////////////////////////

QString qbuPropertyList::CleanUpName(QString strName) const
{
	strName = strName.simplified();

	strName.replace(" ","_");
	if (m_cs == Qt::CaseInsensitive) {
		strName = strName.toUpper();
	}

	return strName;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyList::push_back(qbuPropertyList * pOther)
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

bool qbuPropertyList::fromXML( QString strXML )
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

bool qbuPropertyList::fromXML(QDomElement & domElem)
{
	bool retVal;
	QDomNode n = domElem;
	retVal = !n.isNull();

	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()) {

			qbuProperty prop;
			if (prop.fromXML(e)) {
				push_back(prop);
			}

		}

		n = n.nextSibling();
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuPropertyList::Load( QString strFile )
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

bool qbuPropertyList::Save( QString strFile )
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

int qbuPropertyList::size() const
{
	return m_lstProps.size();
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyList::Print( std::ostream & st,qbuITKIndent indent )
{
	QString str = toXML(true,indent);
	st << qPrintable(str) << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuPropertyList::Print( QTextStream & st, qbuITKIndent indent )
{
	QString str = toXML(true,indent);
	st << str << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////


bool qbuPropertyList::operator==( const qbuPropertyList & other ) const
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