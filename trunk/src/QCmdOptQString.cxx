#include "QCmdOptQString.h"
#include "QCmdParseError.h"
#include "QCmdOptBasicBase.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdOptQString::QCmdOptQString(QString strName, QString strDescription, QString strExplanation,
		QString strDefaultValue, CMDSTRVERIFY pFnVerify ): 
	QCmdOptBasicBase<QString>( strName, strDescription,strExplanation,strDefaultValue), 
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
		retVal = QString("%1 [%2]")
			.arg(GetDescription())
			.arg(m_nValue);

		return retVal;
	}
	/////////////////////////////////////////////////////////////////////////////////////////

	QString QCmdOptQString::exportCommandString()
	{
		QString retVal;
		if (!isDefaultValue() ) {
			retVal = QString("%1").arg(m_nValue);
		}
		return retVal;
	}


/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS