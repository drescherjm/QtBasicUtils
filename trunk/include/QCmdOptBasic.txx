#ifndef __QCMDOPTBASICXX__
#define __QCMDOPTBASICXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QCmdOptBasic<TYPE,fmt>::QCmdOptBasic(QString strName, QString strDescription, 
									 QString strExplanation, TYPE nDefaultValue,
									 TYPE nMinValue, 
									 TYPE nMaxValue) : QCmdOptBasicBaseMM<TYPE>::QCmdOptBasicBaseMM(strName,
									 strDescription,strExplanation,
									 nDefaultValue,nMinValue,nMaxValue
									 )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
int QCmdOptBasic<TYPE,fmt>::ImportData( QString strValue )
{
	int retVal = QCmdPart::MarkSet();
	if ( retVal == 0 ) {
		QString strTemp = strValue.trimmed();
		if ( strTemp.isEmpty() ) {
			retVal = QCmdParseError::PARAM_MISSING_DATA;
		}
		else
		{
			retVal = sscanf(strTemp.toStdString().c_str(),fmt,&this->m_nValue);
			if ( retVal == 1 ) {
				if ( this->m_nValue < this->m_nMinValue ) {
					retVal = QCmdParseError::PARAM_TOO_SMALL;
				}
				else
					if ( this->m_nValue > this->m_nMaxValue ) {
						retVal = QCmdParseError::PARAM_TOO_BIG;
					}
					else
						retVal = QCmdParseError::STATUS_OK;

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

template <class TYPE,char fmt[]>
QString QCmdOptBasic<TYPE,fmt>::GetSyntax()
{
	QString retVal;
	QString tempStr = this->GetDescription() + " [";
	tempStr += fmt;
	tempStr += ("]");
	retVal.sprintf(tempStr.toAscii(),this->m_nDefaultValue);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QString QCmdOptBasic<TYPE, fmt>::exportCommandString()
{
	QString retVal;
	if ( !isDefaultValue() ) {
		retVal = QString("%1%2")
					.arg(exportOptionName())
					.arg(m_nValue);
	}
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDOPTBASICXX__
