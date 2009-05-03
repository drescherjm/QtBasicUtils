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

#endif //__QCMDOPTBASICBASEMMXX__
