#include "xrvariant.h"
#include "Property.h"
#include "PropertyMap.h"

#include <iostream>
#include <QFile>
#include <QTextStream>

using namespace QTUTILS;

int main(int argc, char* argv[])
{
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

	QTUTILS::PropertyMap pc;
	pc.insert(prop);

	prop.setObjectName("Age");
	prop.GetData() = (int)37;
	pc.insert(prop);
	std::cout << prop.toXML().toStdString() << std::endl;

	prop.setObjectName("Sex");
	prop.GetData() = QChar('M');

	std::cout << prop.toXML().toStdString() << std::endl;

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

	QTUTILS::PropertyMap pc1;

	pc1.insert(prop);
		
	std::cout << prop.GetData().typeName() << std::endl;

	{
		QTUTILS::PropertyMap::iterator it = pc1.begin();

		for(;it != pc1.end(); ++it) {
			std::cout << "Name= " << (*it)->objectName().toStdString() << " Type= ";
			std::cout << (*it)->GetData().typeName() << std::endl;
			std::cout << (*it)->toXML().toStdString() << std::endl;
		}
	}
}