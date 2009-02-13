#ifndef __QCMDOPTBASICBASEMM_H__
#define __QCMDOPTBASICBASEMM_H__

#include "QCmdOptBasicBase.h"

namespace QTUTILS {

	template <class TYPE> class QCmdOptBasicBaseMM : public QCmdOptBasicBase<TYPE>
	{
	public:
		QCmdOptBasicBaseMM(QChar ch, QString strDescription, QString strExplanation, 
			TYPE nDefaultValue,TYPE nMinValue, TYPE nMaxValue);
		virtual QString GetSyntax()=0;
		virtual int		ImportData( QString strValue )=0;
	public:
		TYPE	m_nMinValue;
		TYPE	m_nMaxValue;
	};

	/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmdOptBasicBaseMM.txx"

	/////////////////////////////////////////////////////////////////////////////////////////

};//namespace QTUTILS

#endif //__QCMDOPTBASICBASEMM_H__
