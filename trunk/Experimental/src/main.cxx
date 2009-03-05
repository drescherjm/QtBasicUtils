#include "xrvariant.h"
#include "Property.h"
#include "PropertyMap.h"

#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDomNamedNodeMap>

using namespace QTUTILS;


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

bool test_exportXML(QTUTILS::Property & prop) 
{
	std::cout << "BEGIN: Testing test_exportXML" << std::endl;

	QString strXML = prop.toXML();
	QTUTILS::Property prop1;
	prop1.fromXML(strXML);

	std::cout << "Prop= " <<  strXML.toStdString() << std::endl;
	std::cout << "Prop1= " << prop1.toXML().toStdString() << std::endl;


	std::cout << "END: Testing test_exportXML" << std::endl;

	return false;
}

int main(int argc, char* argv[])
{

	int id = qRegisterMetaType<QTUTILS::PropertyMap>();

	int id1 = QMetaType::type("QTUTILS::PropertyMap");

	int id2 = QTUTILS::PropertyMap::m_nMetaID;


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

	QTUTILS::Property prop;

	prop.setObjectName("Name");
	prop.GetData() = QString("John M. Drescher");
	std::cout << prop.toXML().toStdString() << std::endl;

	test_exportXML(prop);

	QTUTILS::PropertyMap pc;
	pc.insert(prop);

	prop.setObjectName("Age");
	prop.GetData() = (int)37;
	pc.insert(prop);
	std::cout << prop.toXML().toStdString() << std::endl;

	test_exportXML(prop);

	prop.setObjectName("Sex");
	prop.GetData() = QChar('M');

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
	PropertyMap::iterator itFind = pc.find(strSearch);
	if ( itFind != pc.end()) {
		std::cout << "Found " << strSearch.toStdString() << std::endl;
		std::cout << (*itFind)->toXML().toStdString() << std::endl;
	}
	else
	{
		std::cout << "Not Found " << strSearch.toStdString() << std::endl;
	}

	prop.setObjectName("Person");
	prop.GetData() = QVariant::fromValue(pc);

	int nUserType= prop.GetData().userType();
	QString str = QMetaType::typeName(nUserType);

	QTUTILS::Property pc2;
	pc2.GetData() = QVariant(nUserType,new QTUTILS::PropertyMap(pc));

	nUserType= pc2.GetData().userType();
	str = QMetaType::typeName(nUserType);

	QTUTILS::PropertyMap pc1;

	pc1.insert(prop);

	prop.setObjectName("Test");
	prop.GetData() = QString("Test");
	pc1.insert(prop);

	QString strXML = pc1.toXML();

	std::cout << strXML.toStdString() << std::endl << std::endl;

	PropertyMap pm;
	pm.fromXML(strXML);

	QString strXML2 = pm.toXML();

	std::cout << strXML2.toStdString() << std::endl << std::endl;
		
	std::cout << prop.GetData().typeName() << std::endl;

	{
		QTUTILS::PropertyMap::iterator it = pc1.begin();

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