#ifndef __QCMDARGBASICBASEMM_H__
#define __QCMDARGBASICBASEMM_H__

#include "QCmdArgBasicBase.h"

namespace QTUTILS {

	template <class TYPE> class QCmdArgBasicBaseMM : public QCmdArgBasicBase<TYPE>
	{
	public:
		QCmdArgBasicBaseMM(QString strName, QString strDescription, QString strExplanation, 
			TYPE nDefaultValue,TYPE nMinValue, TYPE nMaxValue);
		virtual QString GetSyntax()=0;
		virtual int		ImportData( QString strValue )=0;
	public:
		TYPE	m_nMinValue;
		TYPE	m_nMaxValue;
	};

	/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmdArgBasicBaseMM.txx"

	/////////////////////////////////////////////////////////////////////////////////////////

};//namespace QTUTILS

#endif //__QCMDARGBASICBASEMM_H__
