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

	QCmdOptQString::QCmdOptQString( const QCmdOptQString & other ) : SuperClass(other)
	{
		copy(other);
	}

/////////////////////////////////////////////////////////////////////////////////////////

	QCmdOptQString& QCmdOptQString::operator=( const QCmdOptQString & other )
	{

		SuperClass::operator =(other);

		if ( &other != this ) {
			destroy();
			copy(other);
		}

		return (*this);
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
			retVal = QString("%1%2")
				.arg(exportOptionName())
				.arg(m_nValue);
		}
		return retVal;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void QCmdOptQString::copy( const QCmdOptQString & other )
	{
		m_pFnVerify = other.m_pFnVerify;
	}

/////////////////////////////////////////////////////////////////////////////////////////

	void QCmdOptQString::destroy()
	{

	}

/////////////////////////////////////////////////////////////////////////////////////////

QCmdOptQString* QCmdOptQString::Clone()
{
	return new QCmdOptQString(*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS