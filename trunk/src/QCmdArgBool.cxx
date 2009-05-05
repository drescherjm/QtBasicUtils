#include "QCmdArgBool.h"
#include "QCmdParseError.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

QCmdArgBool::QCmdArgBool(QString strName, QString strDescription, QString strExplanation, bool bDefaultValue) : 
QCmdArgBasicBase<bool>( strName, strDescription,strExplanation,bDefaultValue)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdArgBool::ImportData( QString strValue )
{
	int retVal = MarkSet();
	if ( retVal == 0 ) {
		QString strTemp = strValue.trimmed();

		if ( strTemp.length() > 1 ) {
			retVal = QCmdParseError::PARAM_INVALID_DATA;
		}
		else
			if ( strTemp.length() == 1 ) {
				switch(strTemp[0].toAscii()) {
				case '+':
					m_nValue = true;
					break;
				case '-':
					m_nValue = false;
					break;
				default:
					retVal = QCmdParseError::PARAM_INVALID_DATA;
					break;
				};
			}
			else
			{
				m_nValue = true;
			}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdArgBool::GetSyntax()
{
	QString retVal= GetDescription() + " [";
	if ( m_nDefaultValue == true )
		retVal += "TRUE";
	else
		retVal += "FALSE";

	retVal += "]";
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdArgBool::exportCommandString()
{
	QString retVal;
	if ( !isOptional() || !isDefaultValue() ) {
		if ( GetValue() == true )
			retVal = "+";
		else
			retVal = "-";
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS