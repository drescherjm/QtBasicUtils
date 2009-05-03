#ifndef __QCMDOPTBASICBASE_H__
#define __QCMDOPTBASICBASE_H__

#include "QCmdOpt.h"

namespace QTUTILS {

	template <class TYPE> class QCmdOptBasicBase : public QCmdOpt  
	{
	public:
		QCmdOptBasicBase(QString strName, QString strDescription, QString strExplanation, 
			TYPE nDefaultValue);
		virtual QString GetSyntax()=0;
		virtual int		ImportData( QString strValue )=0;
		virtual void	Initialize();
		TYPE	GetValue();
	public:
		TYPE	m_nValue;
		TYPE	m_nDefaultValue;
	};

/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmdOptBasicBase.txx"

/////////////////////////////////////////////////////////////////////////////////////////

};//namespace QTUTILS

#endif //__QCMDOPTBASICBASE_H__
