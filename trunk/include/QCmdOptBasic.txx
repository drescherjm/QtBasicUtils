#ifndef __QCMDOPTBASIC_TXX__
#define __QCMDOPTBASIC_TXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE, QChar fmt[]>
QCmdOptBasic<TYPE,fmt>::QCmdOptBasic(QChar ch, QString strDescription, QString strExplanation, 
									   TYPE nDefaultValue, TYPE nMinValue, TYPE nMaxValue) : 
QCmdOpt( ch, strDescription,strExplanation ), m_nValue(nDefaultValue), 
m_nDefaultValue(nDefaultValue), m_nMinValue(nMinValue),
m_nMaxValue(nMaxValue)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE,QChar fmt[]>
int QCmdOptBasic<TYPE,fmt>::ImportData( QString strValue )
{
	int retVal = MarkSet();
	if ( retVal == 0 ) {
		QString strTemp = strValue.trimmed();
		if ( strTemp.IsEmpty() ) {
			retVal = QCmdParseError::PARAM_MISSING_DATA;
		}
		else
		{
			retVal = _stscanf((LPCTSTR)strTemp,fmt,&m_nValue);
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

template <class TYPE,QChar fmt[]>
QString QCmdOptBasic<TYPE,fmt>::GetSyntax()
{
	QString retVal;
	QString tempStr = _T("%s [");
	tempStr += fmt;
	tempStr += _T("]");
	retVal.Format(tempStr,GetDescription(),m_nDefaultValue);
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE, QChar fmt[]>
void QCmdOptBasic<TYPE,fmt>::Initialize()
{
	m_nValue = m_nDefaultValue;
	QCmdPart::Initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE, QChar fmt[]>
TYPE QCmdOptBasic<TYPE,fmt>::GetValue()
{
	return m_nValue;
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDOPTBASIC_TXX__