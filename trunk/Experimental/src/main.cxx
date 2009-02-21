#include "xrvariant.h"
#include "Property.h"

#include <iostream>
#include <QFile>
#include <QTextStream>

int main(int argc, char* argv[])
{
	QDomDocument domDoc;

	QList<XRVariant> vtList;

	vtList.push_back(QVariant(int(5)));
	vtList.push_back(QVariant(QString("C:/Program Files/")));

	QList<XRVariant>::const_iterator it;

	for(it = vtList.begin(); it != vtList.end();++it) {
		domDoc.insertBefore(it->toDomElement(domDoc),domDoc.firstChild());
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

	std::cout << prop.GetData().typeName() << std::endl;

}