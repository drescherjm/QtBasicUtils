#include "QCmdOptBool.h"
#include "QCmdParseError.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptBool::QCmdOptBool(QChar ch, QString strDescription, QString strExplanation, bool bDefaultValue) : 
QCmdOpt( ch, strDescription,strExplanation ), m_bValue(bDefaultValue), 
m_bDefaultValue(bDefaultValue)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

int QCmdOptBool::ImportData( QString strValue )
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
					m_bValue = true;
					break;
				case '-':
					m_bValue = false;
					break;
				default:
					retVal = QCmdParseError::PARAM_INVALID_DATA;
					break;
				};
			}
			else
			{
				m_bValue = true;
			}
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

void QCmdOptBool::Initialize()
{
	m_bValue = m_bDefaultValue;
	QCmdPart::Initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdOptBool::GetSyntax()
{
	QString retVal = GetDescription();
	
	retVal += " [";
	if ( m_bDefaultValue == true )
		retVal += "TRUE";
	else
		retVal += "FALSE";

	retVal += "]";

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS