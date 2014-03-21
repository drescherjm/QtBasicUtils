#ifndef __QCMDOPTBASICBASEMMXX__
#define __QCMDOPTBASICBASEMMXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdOptBasicBaseMM<TYPE>::QCmdOptBasicBaseMM(QString strName, QString strDescription, QString strExplanation, 
										 TYPE nDefaultValue, TYPE nMinValue, TYPE nMaxValue) : 
QCmdOptBasicBase<TYPE>::QCmdOptBasicBase( strName, strDescription,strExplanation,nDefaultValue ), m_nMinValue(nMinValue),
m_nMaxValue(nMaxValue)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdOptBasicBaseMM<TYPE>::QCmdOptBasicBaseMM( const QCmdOptBasicBaseMM<TYPE> & other ) : QCmdOptBasicBase<TYPE>(other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdOptBasicBaseMM<TYPE>& QCmdOptBasicBaseMM<TYPE>::operator=( const QCmdOptBasicBaseMM<TYPE> & other )
{
	QCmdOptBasicBase<TYPE>::operator =(other);

	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
void QCmdOptBasicBaseMM<TYPE>::destroy()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
void QCmdOptBasicBaseMM<TYPE>::copy( const QCmdOptBasicBaseMM & other )
{
	m_nMaxValue = other.m_nMaxValue;
	m_nMinValue = other.m_nMinValue;
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDOPTBASICBASEMMXX__
