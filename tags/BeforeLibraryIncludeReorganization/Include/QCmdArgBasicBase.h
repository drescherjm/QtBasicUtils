#ifndef __QCMDARGBASICBASE_H__
#define __QCMDARGBASICBASE_H__

#include "QCmdArg.h"

namespace QTUTILS {

	template <class TYPE> class QCmdArgBasicBase : public QCmdArg  
	{
	public:
		QCmdArgBasicBase(QString strName, QString strDescription, QString strExplanation, 
			TYPE nDefaultValue);
		virtual QString GetSyntax()=0;
		virtual int		ImportData( QString strValue )=0;
		virtual void	Initialize();
		virtual bool	isDefaultValue();
		TYPE	GetValue();
		void	SetValue(TYPE nVal);
	public:
		TYPE	m_nValue;
		TYPE	m_nDefaultValue;
	};
	
/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmdArgBasicBase.txx"

/////////////////////////////////////////////////////////////////////////////////////////

};//namespace QTUTILS

#endif //__QCMDARGBASICBASE_H__
