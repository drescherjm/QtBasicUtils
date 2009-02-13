#ifndef __QCMDOPTBASICBASE_H__
#define __QCMDOPTBASICBASE_H__

#include "QCmdOpt.h"

namespace QTUTILS {

	template <class TYPE> class QCmdOptBasicBase : public QCmdOpt  
	{
	public:
		QCmdOptBasicBase(QChar ch, QString strDescription, QString strExplanation, 
			TYPE nDefaultValue,TYPE nMinValue, TYPE nMaxValue);
		virtual QString GetSyntax()=0;
		virtual int		ImportData( QString strValue )=0;
		virtual void	Initialize();
		TYPE	GetValue();
	public:
		TYPE	m_nValue;
		TYPE	m_nDefaultValue;
		TYPE	m_nMinValue;
		TYPE	m_nMaxValue;
	};

/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmdOptBasicBase.txx"

/////////////////////////////////////////////////////////////////////////////////////////

};//namespace QTUTILS

#endif //__QCMDOPTBASICBASE_H__