#ifndef __QCMDARGBASICBASEMMXX__
#define __QCMDARGBASICBASEMMXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdArgBasicBaseMM<TYPE>::QCmdArgBasicBaseMM(QString strName, QString strDescription, QString strExplanation, 
										 TYPE nDefaultValue, TYPE nMinValue, TYPE nMaxValue) : 
QCmdArgBasicBase(strName, strDescription,strExplanation,
				 nDefaultValue ), m_nMinValue(nMinValue),
m_nMaxValue(nMaxValue)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDARGBASICBASEMMXX__
