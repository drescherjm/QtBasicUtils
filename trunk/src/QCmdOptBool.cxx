#include "QCmdOptBool.h"
#include "QCmdParseError.h"

namespace QTUTILS {

/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptBool::QCmdOptBool(QString strName, QString strDescription, QString strExplanation, bool bDefaultValue) : 
QCmdOptBasicBase<bool>( strName, strDescription,strExplanation,bDefaultValue)
{

}
/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptBool::QCmdOptBool( const QCmdOptBool & other ) : SuperClass(other)
{
	copy(other);
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

QString QCmdOptBool::GetSyntax()
{
	QString retVal = GetDescription();
	
	retVal += " [";
	if ( m_nDefaultValue == true )
		retVal += "TRUE";
	else
		retVal += "FALSE";

	retVal += "]";

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdOptBool::getValueDescription()
{
	QString retVal;
	if (GetName() != "?") {
		retVal = "[+- ]";
	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdOptBool::exportCommandString()
{
	QString retVal;
	if ( !isDefaultValue() ) {
		retVal += exportOptionName();

#ifdef  USE_LONG_FORMAT
		if ( GetValue() == true )
			retVal += "+";
		else
			retVal += "-";
#else
		//Since a bool option generally means true if present without the - we can omit
		//the + syntax. For example -B+ can be simplified to -B

		if (!GetValue()) {
			retVal += "-";
		}

#endif //def USE_LONG_FORMAT

	}
	return retVal;
}
/////////////////////////////////////////////////////////////////////////////////////////

void QCmdOptBool::copy( const QCmdOptBool & other )
{
	
}
/////////////////////////////////////////////////////////////////////////////////////////

void QCmdOptBool::destroy()
{

}
/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptBool& QCmdOptBool::operator=( const QCmdOptBool & other )
{
	SuperClass::operator =(other);

	if ( &other != this ) {
		destroy();
		copy(other);
	}

	return (*this);
}
/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptBool* QCmdOptBool::Clone()
{
	return new QCmdOptBool(*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

QString QCmdOptBool::exportOptionName()
{
	QString retVal;
	if (!isExtendedOption()) {
		retVal = "-";
	}
	else
	{
		retVal = "--";
	}

	retVal += GetName();

	return retVal;	
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS