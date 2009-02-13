#ifndef __QCMDARGBASICBASEXX__
#define __QCMDARGBASICBASEXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdArgBasicBase<TYPE>::QCmdArgBasicBase(QString strName, QString strDescription, 
										QString strExplanation, TYPE nDefaultValue, 
										TYPE nMinValue, TYPE nMaxValue) : 
QCmdArg( strName, strDescription,strExplanation ), m_nValue(nDefaultValue), 
m_nDefaultValue(nDefaultValue), m_nMinValue(nMinValue),
m_nMaxValue(nMaxValue)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
void QCmdArgBasicBase<TYPE>::Initialize()
{
	m_nValue = m_nDefaultValue;
	QCmdPart::Initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
TYPE QCmdArgBasicBase<TYPE>::GetValue()
{
	return m_nValue;
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDARGBASICBASEXX__
