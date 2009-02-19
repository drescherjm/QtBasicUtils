#ifndef __QCMDOPTBASICBASEMMXX__
#define __QCMDOPTBASICBASEMMXX__

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE>
QCmdOptBasicBaseMM<TYPE>::QCmdOptBasicBaseMM(QChar ch, QString strDescription, QString strExplanation, 
										 TYPE nDefaultValue, TYPE nMinValue, TYPE nMaxValue) : 
QCmdOptBasicBase<TYPE>::QCmdOptBasicBase( ch, strDescription,strExplanation,nDefaultValue ), m_nMinValue(nMinValue),
m_nMaxValue(nMaxValue)
{

}

/////////////////////////////////////////////////////////////////////////////////////////

#endif //__QCMDOPTBASICBASEMMXX__
