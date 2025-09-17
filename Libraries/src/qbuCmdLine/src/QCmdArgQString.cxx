#include "qbuCmdLinePCH.h"

#include "qbuCmdLine/QCmdArgQString.h"
#include "qbuCmdLine/QCmdParseError.h"
#include "qbuCmdLine/QCmdArgBasicBase.h"
#include <QRegularExpression>

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdArgQString::QCmdArgQString(QString strName, QString strDescription, 
		QString strExplanation, QString strDefaultValue, CMDSTRVERIFY pFnVerify ): 
	QCmdArgBasicBase<QString>( strName, strDescription,strExplanation,strDefaultValue), 
		m_pFnVerify(pFnVerify)
	{

	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdArgQString::QCmdArgQString( const QCmdArgQString & other ) :SuperClass(other)
	{
		copy(other);
	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdArgQString::ImportData( QString strValue )
	{
		int retVal = MarkSet();
		if ( retVal == 0 ) {
			QString strTemp = strValue.trimmed();

			if ( strTemp.isEmpty() ) {
				retVal = QCmdParseError::PARAM_MISSING_DATA;
			}
			else
			{
				if ( m_pFnVerify != NULL ) {
					retVal = (*m_pFnVerify)(strValue,0);
				}
				else
				{
					retVal = QCmdParseError::STATUS_OK;
				}
				if (retVal ==  QCmdParseError::STATUS_OK ) {
					m_nValue = strValue;
				}
			}
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdArgQString::GetSyntax()
	{
		QString retVal = GetDescription() + " [";
		retVal += m_nDefaultValue;
		retVal += "]";
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdArgQString::exportCommandString()
	{
		QString retVal;
		if (!isOptional() || !isDefaultValue()) {
			QRegularExpression whitespaceRegex("\\s+");
			if (m_nValue.contains(whitespaceRegex)) {
				retVal = QString("\"%1\"").arg(m_nValue);
			}
			else {
				retVal = QString("%1").arg(m_nValue);
			}
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdArgQString& QCmdArgQString::operator=( const QCmdArgQString & other )
{
	SuperClass::operator =(other);

	if ( &other != this ) {
		destroy();
		copy(other);
	}

	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdArgQString* QCmdArgQString::Clone()
{
	return new QCmdArgQString(*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdArgQString::copy( const QCmdArgQString & other )
{
	m_pFnVerify = other.m_pFnVerify;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdArgQString::destroy()
{

}

/////////////////////////////////////////////////////////////////////////////////////////
