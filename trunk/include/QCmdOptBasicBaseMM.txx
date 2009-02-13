#ifndef __QCMDOPTBASICBASEMM_TXX__
#define __QCMDOPTBASICBASEMM_TXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdOptBasicBaseMM<TYPE>::QCmdOptBasicBaseMM(QChar ch, QString strDescription, QString strExplanation, 
										 TYPE nDefaultValue, TYPE nMinValue, TYPE nMaxValue) : 
QCmdOptBasicBase( ch, strDescription,strExplanation,nDefaultValue ), m_nMinValue(nMinValue),
m_nMaxValue(nMaxValue)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDOPTBASICBASEMM_TXX__
