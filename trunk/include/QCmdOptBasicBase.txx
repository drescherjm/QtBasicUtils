#ifndef __QCMDORGBASICBASEXX__
#define __QCMDORGBASICBASEXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdOptBasicBase<TYPE>::QCmdOptBasicBase(QString strName, QString strDescription, QString strExplanation, 
									 TYPE nDefaultValue) : 
QCmdOpt( strName, strDescription,strExplanation ), m_nValue(nDefaultValue), 
m_nDefaultValue(nDefaultValue)
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

template <class TYPE>
void QCmdOptBasicBase<TYPE>::SetValue(TYPE nVal)
{
	m_nValue = nVal;
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDORGBASICBASEXX__
