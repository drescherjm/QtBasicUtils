#include "qbuCmdLine/QCmdArgQChar.h"
#include "qbuCmdLine/QCmdArgBasicBaseMM.h"
#include "qbuCmdLine/QCmdParseError.h"
#include <stdio.h>

namespace QTUTILS {
QCmdArgQChar::QCmdArgQChar(QString str, QString strDescription, QString strExplanation, 
	bool bIgnoreCase, QChar chDefaultValue, QChar chMinVal, QChar chMaxVal): 
QCmdArgBasicBaseMM<QChar>( str, strDescription,strExplanation,
	chDefaultValue,chMinVal,chMaxVal),
	m_bIgnoreCase(bIgnoreCase)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdArgQChar::QCmdArgQChar( const QCmdArgQChar & other ) :SuperClass(other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdArgQChar::ImportData( QString strValue )
{
	int retVal = MarkSet();
	if ( retVal == 0 ) {
		QString strTemp = strValue.trimmed();

		if ( strTemp.isEmpty() ) {
			retVal = QCmdParseError::PARAM_MISSING_DATA;
		}
		else
		{
			retVal = sscanf(strTemp.toAscii(),"%c",&m_nValue);
			if ( retVal == 1 ) {
				if ( m_bIgnoreCase && m_nMinValue.isLetter() && m_nMaxValue.isLetter()) {
					if ( m_nValue.toUpper() < m_nMinValue.toUpper() ) {
						retVal = QCmdParseError::PARAM_TOO_SMALL;
					}
					else
						if ( m_nValue.toUpper() > m_nMaxValue.toUpper() ) {
							retVal = QCmdParseError::PARAM_TOO_BIG;
						}
						else
							retVal = QCmdParseError::STATUS_OK;
				}
				else
				{
					if ( m_nValue < m_nMinValue ) {
						retVal = QCmdParseError::PARAM_TOO_SMALL;
					}
					else
						if ( m_nValue > m_nMaxValue ) {
							retVal = QCmdParseError::PARAM_TOO_BIG;
						}
						else
							retVal = QCmdParseError::STATUS_OK;
				}

			}
			else
			{
				retVal = QCmdParseError::PARAM_INVALID_DATA;
			}
		}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdArgQChar::GetSyntax()
{
	QString retVal;
	QString tempStr = GetDescription() + ("%s [");
	tempStr += "%1";
	tempStr += ("]");
	retVal = QString(tempStr).arg(m_nDefaultValue);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdArgQChar::exportCommandString()
{
	QString retVal;
	if (!isOptional() || !isDefaultValue() ) {
		retVal = QString("%1").arg(m_nValue);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdArgQChar& QCmdArgQChar::operator=( const QCmdArgQChar & other )
{
	SuperClass::operator =(other);

	if ( &other != this ) {
		destroy();
		copy(other);
	}

	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdArgQChar* QCmdArgQChar::Clone()
{
	return new QCmdArgQChar(*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdArgQChar::copy( const QCmdArgQChar & other )
{
	m_bIgnoreCase = other.m_bIgnoreCase;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdArgQChar::destroy()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS
