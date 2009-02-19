#include "QCmdArgQString.h"
#include "QCmdParseError.h"
#include "QCmdArgBasicBase.h"

namespace QTUTILS {

	/////////////////////////////////////////////////////////////////////////////////////////

	QCmdArgQString::QCmdArgQString(QString strName, QString strDescription, QString strExplanation,
		QString strDefaultValue, CMDSTRVERIFY pFnVerify ): 
	QCmdArgBasicBase<QString>( strName, strDescription,strExplanation,strDefaultValue), 
		m_pFnVerify(pFnVerify)
	{

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

}; // namespace QTUTILS