#ifndef __QCMDORGBASICBASE_TXX__
#define __QCMDORGBASICBASE_TXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdOptBasicBase<TYPE>::QCmdOptBasicBase(QChar ch, QString strDescription, QString strExplanation, 
									 TYPE nDefaultValue, TYPE nMinValue, TYPE nMaxValue) : 
QCmdOpt( ch, strDescription,strExplanation ), m_nValue(nDefaultValue), 
m_nDefaultValue(nDefaultValue), m_nMinValue(nMinValue),
m_nMaxValue(nMaxValue)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
void QCmdOptBasicBase<TYPE>::Initialize()
{
	m_nValue = m_nDefaultValue;
	QCmdPart::Initialize();
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
TYPE QCmdOptBasicBase<TYPE>::GetValue()
{
	return m_nValue;
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDORGBASICBASE_TXX__
