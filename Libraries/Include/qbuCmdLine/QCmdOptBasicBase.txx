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
QCmdOptBasicBase<TYPE>::QCmdOptBasicBase( const QCmdOptBasicBase<TYPE> & other ) : QCmdOpt(other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdOptBasicBase<TYPE>& QCmdOptBasicBase<TYPE>::operator=( const QCmdOptBasicBase<TYPE> & other )
{
	QCmdOpt::operator =(other);

	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
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

template <class TYPE>
bool QCmdOptBasicBase<TYPE>::isDefaultValue()
{
	return (m_nValue == m_nDefaultValue);
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
void QCmdOptBasicBase<TYPE>::copy( const QCmdOptBasicBase & other )
{
	m_nDefaultValue = other.m_nDefaultValue;
	m_nValue = other.m_nValue;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
void QCmdOptBasicBase<TYPE>::destroy()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDORGBASICBASEXX__
