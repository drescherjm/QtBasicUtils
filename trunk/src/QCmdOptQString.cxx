#include "QCmdOptQString.h"
#include "QCmdParseError.h"
#include "QCmdOptBasicBase.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdOptQString::QCmdOptQString(QChar ch, QString strDescription, QString strExplanation,
		QString strDefaultValue, CMDSTRVERIFY pFnVerify ): 
	QCmdOptBasicBase<QString>( ch, strDescription,strExplanation,strDefaultValue), 
		m_pFnVerify(pFnVerify)
	{

	}

/////////////////////////////////////////////////////////////////////////////////////////

	int QCmdOptQString::ImportData( QString strValue )
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

	QString QCmdOptQString::GetSyntax()
	{
		QString retVal;
		QString tempStr = GetDescription() + " [";
		tempStr += "%s";
		tempStr += ("]");
		retVal.sprintf(tempStr.toAscii(),m_nDefaultValue);
		return retVal;
	}
	
/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS