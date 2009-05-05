#ifndef __QCMDARGBASICBASEXX__
#define __QCMDARGBASICBASEXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdArgBasicBase<TYPE>::QCmdArgBasicBase(QString strName, QString strDescription, 
										QString strExplanation, TYPE nDefaultValue) : 
QCmdArg( strName, strDescription,strExplanation ), m_nValue(nDefaultValue), 
m_nDefaultValue(nDefaultValue)
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

template <class TYPE>
void QCmdArgBasicBase<TYPE>::SetValue(TYPE nValue)
{
	m_nValue = nValue;
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDARGBASICBASEXX__
