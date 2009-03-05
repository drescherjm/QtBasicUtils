#include "Property.h"
#include "PropertyMap.h"

#include <QRegExp>
#include <QDomDocument>

namespace QTUTILS {

#if 0

//////////////////////////////////////////////////////////////////////////////////////////

class ParsePropXML
{
public:
	ParsePropXML();
public:
	Property&	GetProp();
	bool		Parse(QString strXml);
	QString		GetName();
protected:
	bool	SetupParse(QString strXml);
	bool	ParseObjName();
	bool	ParseBeginTag();
	bool	ParseEndTag();
	bool	ParseBool();
	bool	ParseValue();
	bool	ParseType();
	bool	ParseInt();
	bool	ParseByte();
	bool	ParseWord();
	bool	ParseDWord();
	bool	ParseString();
protected:
	QString			m_strBeginTag;
	QString			m_strExXML;
	QString			m_strObjName;
	QVariant::Type	m_nTypeID;
	QString			m_strObjIDName;
	Property		m_prop;
};

//////////////////////////////////////////////////////////////////////////////////////////

ParsePropXML::ParsePropXML()
{
	m_nTypeID = QVariant::Invalid;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::SetupParse(QString strXML)
{
	bool retVal;
	strXML = strXML.trimmed();
	retVal = strXML.length() > 2;
	if (retVal) {
		retVal = (strXML[0] == '<');
		if (retVal) {
			retVal = (strXML[strXML.length()-1] == '>');
			if (retVal) {
				m_strExXML = strXML.mid(1,strXML.length()-2);
			}
		}
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseObjName()
{
	bool retVal = !m_strExXML.isEmpty();
	if (retVal) {
		m_strExXML = m_strExXML.trimmed();
		int pos = m_strExXML.indexOf(QRegExp("\\s"),0);
		retVal = (pos > 0);
		if (retVal) {
			m_strObjIDName = m_strExXML.left(pos);
		}
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseEndTag()
{
	bool retVal = !m_strExXML.isEmpty();
	if (retVal) {
		m_strExXML = m_strExXML.trimmed();
		int nPos = m_strExXML.lastof("</");
		retVal = (nPos > m_strObjIDName.length());
		if (retVal) {
			int nStart = nPos;
			while (nStart > 0) {
				nStart = m_strExXML.indexOf(QRegExp("\\s"),nPos);
				if (nStart >0) {
					m_strExXML.Delete(nStart,1);
				}
			}
			QString strTemp;
			strTemp.Format("</%s",m_strObjIDName);
			retVal = (m_strExXML.Right(strTemp.GetLength())	== strTemp);
			if (retVal) {
				m_strExXML=m_strExXML.Left(nPos);
			}
			
		}
		
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseBeginTag()
{
	bool retVal;
	retVal = (m_strExXML.Left(m_strObjIDName.GetLength()) == m_strObjIDName);
	if (retVal) {
		m_strExXML = m_strExXML.Mid(m_strObjIDName.GetLength());
		m_strExXML.TrimLeft();
		int nPos = m_strExXML.Find(">");
		retVal = (nPos > 0);
		if (retVal) {
			m_strBeginTag = m_strExXML.Left(nPos);
			m_strBeginTag.MakeLower();
			m_strExXML = m_strExXML.Mid(nPos+1);
		}
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::Parse(QString strXml)
{
	bool retVal = SetupParse(strXml);
	if (retVal) {
		retVal = ParseObjID();
		if (retVal) {
			retVal = ParseEndTag();
			if (retVal) {
				retVal = ParseBeginTag();
				if (retVal) {
					retVal = ParseType();
					if (retVal) {
						retVal = ParseValue();
					}
				}
			}
		}
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool PROPERTY::ImportXML(QString strXML)
{
	bool retVal;
	ParsePropXML parser;
	retVal = parser.Parse(strXML);
	if (retVal) {
		operator=(parser.GetProp());
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseType()
{
	bool retVal;
	QStringEx strType(m_strBeginTag.GetDelimitedField("ty=\"","\""));
	retVal = (!strType.IsEmpty());
	if (retVal) {
		strType.RemoveExtraSpaces(TRUE,TRUE,TRUE);
		retVal = (!strType.IsEmpty());
		if (retVal) {
			if (strType[0] == '0') {
					m_nTypeID = static_cast<BYTE>(_tcstol(static_cast<LPCTSTR>(strType),NULL,16));
				}
				else
					m_nTypeID = static_cast<BYTE>(_tcstol(static_cast<LPCTSTR>(strType),NULL,10));
		}
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseValue()
{
	bool retVal;
	retVal = !m_strExXML.IsEmpty();
	if (retVal) {
		switch(m_nTypeID & PROPERTY::TYPE_MASK) {
		case PROPERTY::PC_bool:
			retVal = ParseBool();
			break;
		case PROPERTY::PC_INT:
			retVal = ParseInt();
			break;
		case PROPERTY::PC_WORD:
			retVal = ParseWord();
			break;
		case PROPERTY::PC_DWORD:
			retVal = ParseDWord();
			break;
		case PROPERTY::PC_BYTE:
			retVal = ParseByte();
			break;
		case PROPERTY::PC_STRING:
			retVal = ParseString();
			break;
		default:
			retVal = FALSE;
		}
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseBool()
{
	bool retVal = FALSE;
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseInt()
{
	bool retVal = TRUE;
	int data;
	if (m_strExXML[0] == '0') {
		data = static_cast<int>(_tcstol(static_cast<LPCTSTR>(m_strExXML),NULL,16));
	}
	else
		data = static_cast<int>(_tcstol(static_cast<LPCTSTR>(m_strExXML),NULL,10));

	m_prop.SetVal(m_nObjID,data);

	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseWord()
{
	bool retVal = TRUE;
	WORD data;
	if (m_strExXML[0] == '0') {
		data = static_cast<WORD>(_tcstol(static_cast<LPCTSTR>(m_strExXML),NULL,16));
	}
	else
		data = static_cast<WORD>(_tcstol(static_cast<LPCTSTR>(m_strExXML),NULL,10));

	m_prop.SetVal(m_nObjID,data);

	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseDWord()
{
	bool retVal = TRUE;
	DWORD data;
	if (m_strExXML[0] == '0') {
		data = static_cast<DWORD>(_tcstol(static_cast<LPCTSTR>(m_strExXML),NULL,16));
	}
	else
		data = static_cast<DWORD>(_tcstol(static_cast<LPCTSTR>(m_strExXML),NULL,10));

	m_prop.SetVal(m_nObjID,data);

	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseString()
{
	QString data=m_strExXML;
	m_prop.SetVal(m_nObjID,data);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool ParsePropXML::ParseByte()
{
	bool retVal = TRUE;
	BYTE data;
	if (m_strExXML[0] == '0') {
		data = static_cast<BYTE>(_tcstol(static_cast<LPCTSTR>(m_strExXML),NULL,16));
	}
	else
		data = static_cast<BYTE>(_tcstol(static_cast<LPCTSTR>(m_strExXML),NULL,10));

	m_prop.SetVal(m_nObjID,data);

	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

Property& ParsePropXML::GetProp()
{
	return m_prop;
}


#endif //0

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

QVariant& Property::GetData()
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
		retVal = pc.toXML();

		QString strTemp = QString("<%1 tyID=\"%2\" tyName=\"%3\">\n%4</%1>\n")
			.arg(strName)
			.arg(ty)
			.arg(GetData().typeName())
			.arg(retVal);

		retVal = strTemp;
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

bool Property::fromXML( QDomElement & docElem)
{
	bool retVal = !docElem.isNull();
	if (retVal) {
		QString strTypeID = docElem.attribute("tyID");
		retVal = !strTypeID.isEmpty();
		if (retVal) {
			QVariant::Type ty = static_cast<QVariant::Type>(strTypeID.toUInt());
			if ((ty != QVariant::UserType) && (ty != QVariant::Invalid)) {
				m_vt = docElem.text();
				retVal = m_vt.canConvert(ty);
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
					}
				}
		}
	}

	return retVal;
}

//////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS