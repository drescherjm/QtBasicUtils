#include "Property.h"
#include "PropertyMap.h"

#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QDomDocument>

namespace QTUTILS {

//////////////////////////////////////////////////////////////////////////////////////////

Property::Property()
{
}

//////////////////////////////////////////////////////////////////////////////////////////

Property::~Property()
{
	destroy();
}

//////////////////////////////////////////////////////////////////////////////////////////

Property::Property(const Property & other)
{
	copy(other);
}

//////////////////////////////////////////////////////////////////////////////////////////

Property& Property::operator =(const Property & other)
{
	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Property::copy(const Property & other)
{
	m_vt = other.m_vt;
	setObjectName(other.objectName());
}

//////////////////////////////////////////////////////////////////////////////////////////

void Property::destroy()
{

}

//////////////////////////////////////////////////////////////////////////////////////////

const QVariant& Property::GetData() const
{
	return m_vt;
}

//////////////////////////////////////////////////////////////////////////////////////////

QString	Property::toXML()
{
	QString retVal;
	QVariant::Type ty = GetData().type();

	if (ty < QVariant::UserType) {
		QString strName = objectName();
		retVal = GetData().toString();
		QString strTemp = QString("<%1 tyID=\"%2\" tyName=\"%3\">%4</%1>\n")
			.arg(strName)
			.arg(ty)
			.arg(GetData().typeName())
			.arg(retVal);
		retVal = strTemp;
	}
	else if (GetData().canConvert<PropertyMap>()) {
		PropertyMap pc = GetData().value<PropertyMap>();
		QString strName = objectName();
		retVal = pc.toXML(false); // The PropertyMap is a root node

		QString strTemp = QString("<%1 tyID=\"%2\" tyName=\"%3\">\n%4</%1>\n")
			.arg(strName)
			.arg(ty)
			.arg(GetData().typeName())
			.arg(retVal);

		retVal = strTemp;
	}
	else  if (GetData().canConvert<UserPropPtr>()) {
		UserPropPtr ptr = GetData().value<UserPropPtr>();
		if (!ptr.isNull()) {
			retVal = ptr.toXML(false);
			QString strName = objectName();

			QString strTemp = QString("<%1 tyID=\"%2\" tyName=\"%3\">\n%4</%1>\n")
				.arg(strName)
				.arg(ty)
				.arg(GetData().typeName())
				.arg(retVal);

			retVal = strTemp;
		}

	}
	return retVal;

}

//////////////////////////////////////////////////////////////////////////////////////////

bool Property::fromXML(QString strXML)
{
	QDomDocument doc;
	bool retVal = doc.setContent(strXML);
	if (retVal) {
		QDomElement docElem = doc.documentElement();
		retVal = fromXML(docElem);
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool Property::fromXML(QDomElement & docElem)
{
	bool retVal = !docElem.isNull();
	if (retVal) {
		QString strTypeID = docElem.attribute("tyID");
		retVal = !strTypeID.isEmpty();
		if (retVal) {
			QVariant::Type ty = static_cast<QVariant::Type>(strTypeID.toUInt());
			if ((ty != QVariant::UserType) && (ty != QVariant::Invalid)) {
				
				QString strText = docElem.text();
				switch(ty){
					// This case fails so we do the conversion manually
					case QVariant::Char:
						if (!strText.isEmpty()) {
							m_vt = QChar(strText[0]);
						}
						else
							m_vt =QChar();
						
						break;
					default:
						m_vt = strText;
						retVal = m_vt.canConvert(ty);
						break;
				}
				
				if (retVal) {
					m_vt.convert(ty);
					setObjectName(docElem.tagName());
				}
			}
			else
				if (ty == QVariant::UserType) {
					QString strTypeName = docElem.attribute("tyName");
					retVal = !strTypeName.isEmpty();
					if (retVal) {
#if 0
						QString strType = strTypeName.right(11);
						QString strTest = "PropertyMap";
						if (strType.compare(strTest,Qt::CaseInsensitive) == 0) {

							PropertyMap pm;
							
							QDomNode n = docElem.firstChild();

							retVal = !n.isNull();

							if (retVal) {
								QDomElement e = n.toElement();
								retVal = !e.isNull();
								if (retVal) {
									pm.fromXML(e);
									GetData() = QVariant::fromValue(pm);
									setObjectName(docElem.tagName());
								}
							}
						}
#else						
						int nId = QMetaType::type(strTypeName.toStdString().c_str());

						void* ptr = QMetaType::construct(nId);

						UserProperty* pProp = reinterpret_cast<UserProperty*>(ptr);
						if (pProp) {
							QDomNode n = docElem.firstChild();

							retVal = !n.isNull();

							if (retVal) {
								QDomElement e = n.toElement();
								retVal = !e.isNull();
								if (retVal) {
									pProp->fromXML(e);
									SetData(QVariant(nId,pProp));

									setObjectName(docElem.tagName());
								}
							}
							QMetaType::destroy(nId,ptr);
						}
#endif 
					}
				}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QVariant& Property::SetData( const QVariant& vt )
{
	m_vt = vt;
	Modify();
	return m_vt;
}

/////////////////////////////////////////////////////////////////////////////////////////

QVariant& Property::SetData( const UserPropPtr & ptr )
{
	m_vt = QVariant::fromValue<UserPropPtr>(ptr);
	Modify();
	return m_vt;
}

/////////////////////////////////////////////////////////////////////////////////////////

Property::operator UserPropPtr() const
{
	return GetData().value<UserPropPtr>();
}
//////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////

bool Property::Load( QString strFile )
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

bool Property::Save( QString strFile )
{
	QString strXML = toXML();
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