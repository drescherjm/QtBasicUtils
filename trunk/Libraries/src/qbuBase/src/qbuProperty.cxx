#include "qbuBase/qbuProperty.h"
#include "qbuBase/qbuPropertyMap.h"
#include "qbuBase/qbuPropXMLHelper.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QDomDocument>
#include "qbuBase/qbuPropertyTypeNameAlias.h"



//////////////////////////////////////////////////////////////////////////////////////////

qbuProperty::qbuProperty()
{
}

//////////////////////////////////////////////////////////////////////////////////////////

qbuProperty::~qbuProperty()
{
	destroy();
}

//////////////////////////////////////////////////////////////////////////////////////////

qbuProperty::qbuProperty(const qbuProperty & other)
{
	copy(other);
}

//////////////////////////////////////////////////////////////////////////////////////////

qbuProperty& qbuProperty::operator =(const qbuProperty & other)
{
	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

//////////////////////////////////////////////////////////////////////////////////////////

void qbuProperty::copy(const qbuProperty & other)
{
	m_vt = other.m_vt;
	setObjectName(other.objectName());
}

//////////////////////////////////////////////////////////////////////////////////////////

void qbuProperty::destroy()
{

}

//////////////////////////////////////////////////////////////////////////////////////////

const QVariant& qbuProperty::GetData() const
{
	return m_vt;
}

//////////////////////////////////////////////////////////////////////////////////////////

QString	qbuProperty::toXML(qbuITKIndent indent)
{
	QString retVal;
	QVariant::Type ty = GetData().type();

	if (ty < QVariant::UserType) {
		QString strName = objectName();

		switch(ty) {
		case QVariant::Char:
			{
				QChar ch = GetData().toChar();
				ushort nVal = ch.unicode();

				retVal = QString("0x%1").arg(nVal,3,16,QChar('0'));
				//retVal = QString("\'%1\'").arg(ch);
			}
			break;
		default:
			retVal = GetData().toString();
		}
		
		QString strTemp = QString("%1<%2 tyID=\"%3\" tyName=\"%4\">%5</%2>\n")
			.arg(indent.getIndent())
			.arg(strName)
			.arg(ty)
			.arg(GetData().typeName())
			.arg(retVal);
		retVal = strTemp;
	}
	else if (GetData().canConvert<qbuPropertyMap>()) {
		qbuPropertyMap pc = GetData().value<qbuPropertyMap>();
		QString strName = objectName();
		retVal = pc.toXML(false,indent); // The PropertyMap is a root node

		QString strTemp = QString("%1<%2 tyID=\"%3\" tyName=\"%4\">\n%5%1</%2>\n")
			.arg(indent.getIndent())
			.arg(strName)
			.arg(ty)
			.arg(GetData().typeName())
			.arg(retVal);

		retVal = strTemp;
	}
	else  if (GetData().canConvert<qbuUserPropPtr>()) {
		qbuUserPropPtr ptr = GetData().value<qbuUserPropPtr>();
		if (!ptr.isNull()) {
			retVal = ptr.toXML(false,indent);
			QString strName = objectName();

			QString strTypeName = qbuPropertyTypeNameAlias::instance()->getAlias(GetData().typeName());

			QString strTemp = QString("%1<%2 tyID=\"%3\" tyName=\"%4\">\n%5%1</%2>\n")
				.arg(indent.getIndent())
				.arg(strName)
				.arg(ty)
				.arg(strTypeName)
				.arg(retVal);

			retVal = strTemp;
		}

	}
	return retVal;

}

//////////////////////////////////////////////////////////////////////////////////////////

bool qbuProperty::fromXML(QString strXML)
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

bool qbuProperty::fromXML(QDomElement & docElem)
{
	bool retVal = !docElem.isNull();
	if (retVal) {
		QString strTypeID = docElem.attribute("tyID");
		retVal = !strTypeID.isEmpty();
		if (!retVal) {
			// Assume the type is a QString if the xml did not specify the type.
			strTypeID = QString("%1").arg(QVariant::String);
			retVal = true;
		}
		if (retVal) {
			QVariant::Type ty = static_cast<QVariant::Type>(strTypeID.toUInt());
			if ((ty != QVariant::UserType) && (ty != QVariant::Invalid)) {
				
				QString strText = docElem.text();
				switch(ty){
					// This case fails so we do the conversion manually
					case QVariant::Char:
						if (!strText.isEmpty()) {
							if (strText.startsWith("0x",Qt::CaseInsensitive)) {
								strText.remove("0x",Qt::CaseInsensitive);
								m_vt = QChar(strText.toInt(&retVal,16));
							}
							else
							{
								m_vt = QChar(strText.toInt(&retVal,10));
							}
							
							//m_vt = QChar(strText[0]);
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
						qbuUserPropXMLHelper* pHlpr = qbuPropXMLHelper::instance()->GetXMLHelper(strTypeName);
						retVal = (pHlpr != NULL);
						if (retVal) {
							retVal = pHlpr->fromXML(this,docElem);
						}
					}
				}
		}
	}

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*  SetData sets value of the Property to the user supplied QVariant.  Also after the 
*  value is set the Modified flag is set.
*/

QVariant& qbuProperty::SetData( const QVariant& vt )
{
	m_vt = vt;
	Modify();
	return m_vt;
}

/////////////////////////////////////////////////////////////////////////////////////////

/**
*  SetData sets value of the Property to the user supplied UserPropPtr.  Also after the 
*  value is set the Modified flag is set.
*/

QVariant& qbuProperty::SetData( const qbuUserPropPtr & ptr )
{
	m_vt = QVariant::fromValue<qbuUserPropPtr>(ptr);
	Modify();
	return m_vt;
}

/////////////////////////////////////////////////////////////////////////////////////////

qbuProperty::operator qbuUserPropPtr() const
{
	return GetData().value<qbuUserPropPtr>();
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
*	Load reads the Property from and XML file.
*/

bool qbuProperty::Load( QString strFile )
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

/**
 *	Save exports the Property to XML and saves that. After the save the Modified flag
 *  is reset.
 */

bool qbuProperty::Save( QString strFile )
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

void qbuProperty::Print( std::ostream & st, qbuITKIndent indent )
{
	QString str = toXML(indent);
	st << qPrintable(str) << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////

void qbuProperty::Print( QTextStream & st, qbuITKIndent indent )
{
	QString str = toXML(indent);
	st << str << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool qbuProperty::operator==( const qbuProperty & other ) const
{
	return m_vt == other.m_vt;
}

/////////////////////////////////////////////////////////////////////////////////////////
