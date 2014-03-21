#ifndef __QCmdArgBasicBaseMMMMXX__
#define __QCmdArgBasicBaseMMMMXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdArgBasicBaseMM<TYPE>::QCmdArgBasicBaseMM(QString strName, QString strDescription, QString strExplanation, 
		TYPE nDefaultValue, TYPE nMinValue, TYPE nMaxValue) : 
                SuperClass::QCmdArgBasicBase(strName, strDescription,strExplanation,
		nDefaultValue ), m_nMinValue(nMinValue),
                m_nMaxValue(nMaxValue)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
void QCmdArgBasicBaseMM<TYPE>::destroy()
{

}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
void QCmdArgBasicBaseMM<TYPE>::copy( const QCmdArgBasicBaseMM<TYPE> & other )
{
	m_nMaxValue = other.m_nMaxValue;
	m_nMinValue = other.m_nMinValue;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdArgBasicBaseMM<TYPE>& QCmdArgBasicBaseMM<TYPE>::operator=( const QCmdArgBasicBaseMM<TYPE> & other )
{
	SuperClass::operator =(other);

	if ( &other != this ) {
		destroy();
		copy(other);
	}
	return (*this);
}

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdArgBasicBaseMM<TYPE>::QCmdArgBasicBaseMM( const QCmdArgBasicBaseMM<TYPE> & other ) : SuperClass(other)
{
	copy(other);
}

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCmdArgBasicBaseMMMMXX__

