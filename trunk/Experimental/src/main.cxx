#include "xrvariant.h"
#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuBase/qbuPropertyList.h"

#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDomNamedNodeMap>
#include <QtCore/QCoreApplication>
#include <QRegExp>
#include <QStringList>
#include <QDebug>

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

bool test_exportXML(qbuProperty & prop) 
{
	std::cout << "BEGIN: Testing test_exportXML" << std::endl;

	QString strXML = prop.toXML();
	qbuProperty prop1;
	prop1.fromXML(strXML);

	std::cout << "Prop= " <<  strXML.toStdString() << std::endl;
	std::cout << "Prop1= " << prop1.toXML().toStdString() << std::endl;


	std::cout << "END: Testing test_exportXML" << std::endl;

	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

void test_match_quotes(const QString& text, const QString& pattern)
{
	qDebug() << "testing " << text << " against " << pattern;
	QRegExp rx(pattern);
	int pos = 0;

	QStringList lst;
	while ((pos = rx.indexIn(text, pos)) != -1) {
		//qDebug() << rx.capturedTexts();
		qDebug() << rx.cap(1);

		lst << rx.cap(1);
		pos += rx.matchedLength();
	}

	int x=1;
}

/////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{

	//test_match_quotes( "test \"a string\" \"string \\\" escaped\" 1 2", "([\"])(?:.)*([\"])");
	//test_match_quotes( "test \"a string\" \"string \\\" escaped\" 1 2", "((\")(?:\\\\?.)*?\\2)");

	test_match_quotes(
		"'john drescher' test \"a string\" \"string \\\" escaped\" 1 2",
		"((?:[^\\s\"]+)|(?:\"(?:\\\\\"|[^\"])*\"))|((?:[^\\s\']+)|(?:\'(?:\\\\\'|[^\'])*\'))");


	test_match_quotes(
		"'john drescher' test \"a string\" \"string \\\" escaped\" 1 2",
		"((?:[^\\s\']+)|(?:\'(?:\\\\\'|[^\'])*\'))");


	test_match_quotes(
		"'john drescher' test \"a string\" \"string \\\" escaped\" 1 2",
		"((?:[^\\s\"]+)|(?:\"(?:\\\\\"|[^\"])*\")|(?:[^\\s\']+)|(?:\'(?:\\\\\'|[^\'])*\'))");
	

	test_match_quotes(
		"'john drescher' test \"a string\" \"string 'harder' \\\" escaped\" 1 2",
		"((?:[^\\s\"]+)|(?:\"(?:\\\\\"|[^\"])*\")|(?:[^\\s\']+)|(?:\'(?:\\\\\'|[^\'])*\'))");

	test_match_quotes(
		"'john \"d\"rescher' test \"a string\" \"string 'harder' \\\" escaped\" 1 2",
		"((?:[^\\s\"]+)|(?:\"(?:\\\\\"|[^\"])*\")|(?:[^\\s\']+)|(?:\'(?:\\\\\'|[^\'])*\'))");

	QString strMsg0 = "'john drescher' test \"a string\" \"string \\\" escaped\" 1 2";

	QStringList lst = strMsg0.split(QRegExp("((?:[^\\s\"]+)|(?:\"(?:\\\\\"|[^\"])*\")|(?:[^\\s\']+)|(?:\'(?:\\\\\'|[^\'])*\'))"));


	int id = qRegisterMetaType<qbuPropertyMap>();

	int id1 = QMetaType::type("PropertyMap");

	//int id2 = PropertyMap::m_nMetaID;


	{
		qbuPropertyMap map;

		qbuPropertyMap::const_iterator it = map.find("John");
		if (it != map.end()) {
			std::cerr << "Something bad happened" << std::endl;
		}
	}


	QDomDocument domDoc;

	QList<XRVariant> vtList;

	vtList.push_back(QVariant(int(5)));
	vtList.push_back(QVariant(QString("C:/Program Files/")));

	QList<XRVariant>::const_iterator it;

	for(it = vtList.begin(); it != vtList.end();++it) {

		QDomNode xmlNode = it->toDomElement(domDoc);
		domDoc.insertBefore(xmlNode,domDoc.firstChild());
	}

	QFile file("test.xml");

	if (file.open(QFile::WriteOnly|QFile::Text)) {
		QTextStream stream(&file);
		QDomNode xmlNode = domDoc.createProcessingInstruction("xml",
			"version=\"1.0\" encoding=\"ISO-8859-1\"");
		domDoc.insertBefore(xmlNode,domDoc.firstChild());
		domDoc.save(stream,4);
	}

	qbuProperty prop;

	prop.setObjectName("Name");
	prop.SetData(QString("John M. Drescher"));
	std::cout << prop.toXML().toStdString() << std::endl;

	test_exportXML(prop);

	qbuPropertyMap pc;
	pc.insert(prop);

	prop.setObjectName("Age");
	prop.SetData((int)37);
	pc.insert(prop);
	std::cout << prop.toXML().toStdString() << std::endl;

	test_exportXML(prop);

	prop.setObjectName("Sex");
	prop.SetData(QChar('M'));

	test_exportXML(prop);

	std::cout << prop.toXML().toStdString() << std::endl;

	{
		QDomDocument doc;
		if (doc.setContent(prop.toXML())) {
			QDomElement docElem = doc.documentElement();
			printDomElem(docElem);
		}
	}

	pc.insert(prop);

	QString strSearch("age");
	qbuPropertyMap::iterator itFind = pc.find(strSearch);
	if ( itFind != pc.end()) {
		std::cout << "Found " << strSearch.toStdString() << std::endl;
		std::cout << (*itFind)->toXML().toStdString() << std::endl;
	}
	else
	{
		std::cout << "Not Found " << strSearch.toStdString() << std::endl;
	}

	prop.setObjectName("Person");
	prop.SetData(QVariant::fromValue(pc));

	int nUserType= prop.GetData().userType();
	QString str = QMetaType::typeName(nUserType);

	qbuProperty pc2;
	pc2.SetData(qbuUserPropPtr(new qbuPropertyMap(pc)));

	str = pc2.toXML();

	if (pc2.GetData().canConvert<qbuUserPropPtr>()) {
		qbuUserPropPtr ptr = pc2.GetData().value<qbuUserPropPtr>();
		str = ptr.toXML();
		qbuUserPropPtr ptr1 = pc2;
		QString str_1 = ptr1.toXML();
		qbuPropertyMap* pPM1 = dynamic_cast<qbuPropertyMap*>(ptr1.data());
		if (pPM1) {
			prop.SetData(QDate(1972,1,10));
			prop.setObjectName("DOB");
			pPM1->insert(prop);
		}
		QString str_2 = ptr1.toXML();
	}

	nUserType= pc2.GetData().userType();
	str = QMetaType::typeName(nUserType);

	qbuUserProperty* pProp2 = pc2.GetData().value<qbuUserProperty*>();
	qbuPropertyMap* pProp3 = pc2.GetData().value<qbuPropertyMap*>();

	qbuPropertyMap pc1;

	pc1.insert(prop);

	prop.setObjectName("Test");
	prop.SetData(QString("Test"));
	pc1.insert(prop);

	QString strXML = pc1.toXML();

	std::cout << strXML.toStdString() << std::endl << std::endl;

	qbuPropertyMap pm;
	pm.fromXML(strXML);

	QString strXML2 = pm.toXML();

	std::cout << strXML2.toStdString() << std::endl << std::endl;
		
	std::cout << prop.GetData().typeName() << std::endl;

	{
		qbuPropertyMap::iterator it = pc1.begin();

		for(;it != pc1.end(); ++it) {
			std::cout << "Name= " << (*it)->objectName().toStdString() << " Type= ";
			std::cout << (*it)->GetData().typeName() << std::endl;
			std::cout << (*it)->toXML().toStdString() << std::endl;

			if ( (*it)->GetData().type() == QVariant::UserType ) {
				QDomDocument doc;
				if (doc.setContent((*it)->toXML())) {
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

				}
			}
		}
	}
}
