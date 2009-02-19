#ifndef __QCMDOPTBASICXX__
#define __QCMDOPTBASICXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
QCmdOptBasic<TYPE,fmt>::QCmdOptBasic(QChar ch, QString strDescription, 
									 QString strExplanation, TYPE nDefaultValue,
									 TYPE nMinValue, 
									 TYPE nMaxValue) : QCmdOptBasicBaseMM(ch,
									 strDescription,strExplanation,
									 nDefaultValue,nMinValue,nMaxValue
									 )
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,char fmt[]>
int QCmdOptBasic<TYPE,fmt>::ImportData( QString strValue )
{
	int retVal = MarkSet();
	if ( retVal == 0 ) {
		QString strTemp = strValue.trimmed();
		if ( strTemp.isEmpty() ) {
			retVal = QCmdParseError::PARAM_MISSING_DATA;
		}
		else
		{
			retVal = sscanf(strTemp.toStdString().c_str(),fmt,&m_nValue);
			if ( retVal == 1 ) {
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
	QString tempStr = GetDescription() + " [";
	tempStr += fmt;
	tempStr += ("]");
	retVal.sprintf(tempStr.toAscii(),m_nDefaultValue);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDOPTBASICXX__
