#ifndef __QCMDARGBASICBASE_H__
#define __QCMDARGBASICBASE_H__

#include "QCmdOpt.h"

namespace QTUTILS {

	template <class TYPE> class QCmdArgBasicBase : public QCmdArg  
	{
	public:
		QCmdArgBasicBase(QString strName, QString strDescription, QString strExplanation, 
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

#include "QCmdArgBasicBase.txx"

/////////////////////////////////////////////////////////////////////////////////////////

};//namespace QTUTILS

#endif //__QCMDARGBASICBASE_H__