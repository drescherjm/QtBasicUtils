#include "QCmdArgQChar.h"
#include "QCmdArgBasicBaseMM.h"
#include "QCmdParseError.h"

namespace QTUTILS {
	QCmdArgQChar::QCmdArgQChar(QString str, QString strDescription, QString strExplanation, 
		bool bIgnoreCase, QChar chDefaultValue, QChar chMinVal, QChar chMaxVal): 
	QCmdArgBasicBaseMM<QChar>( str, strDescription,strExplanation,
		chDefaultValue,chMinVal,chMaxVal),
		m_bIgnoreCase(bIgnoreCase)
	{

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
		QString tempStr = ("%s [");
		tempStr += "%c";
		tempStr += ("]");
		retVal.sprintf(tempStr.toAscii(),GetDescription(),m_nDefaultValue);
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS