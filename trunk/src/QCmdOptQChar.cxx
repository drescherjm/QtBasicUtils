#include "QCmdOptQChar.h"
#include "QCmdParseError.h"

namespace QTUTILS {
	QCmdOptQChar::QCmdOptQChar(QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase, 
		QChar chDefaultValue, QChar chMinVal, QChar chMaxVal): 
	QCmdOptBasicBaseMM<QChar>( strName, strDescription,strExplanation,
		chDefaultValue,chMinVal,chMaxVal),
		m_bIgnoreCase(bIgnoreCase)
	{

	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdOptQChar::ImportData( QString strValue )
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

	QString QCmdOptQChar::GetSyntax()
	{
		QString retVal;
		QString tempStr = GetDescription() + (" [");
		tempStr += "%1";
		tempStr += ("]");
		retVal = QString(tempStr).arg(m_nDefaultValue);
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdOptQChar::exportCommandString()
	{
		QString retVal;
		if (!isDefaultValue() ) {
			retVal = QString("%1").arg(m_nValue);
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS