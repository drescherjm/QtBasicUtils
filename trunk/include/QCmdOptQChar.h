#ifndef __QCMDOPTQCHAR_H__
#define __QCMDOPTQCHAR_H__

#include "QCmdOptBasic.h"

namespace QTUTILS {
	
	class CCmdOptQChar : public QCmdOptBasic<QChar  
	{
	public:
		CCmdOptTCHAR(TCHAR ch, CString strDescription, CString strExplanation, BOOL bIgnoreCase, 
			TCHAR chDefaultValue, TCHAR chMinVal, TCHAR chMaxVal);
		virtual int		ImportData( CString strValue );
		virtual void	Initialize();
		TCHAR	GetValue();
	public:
		virtual CString GetSyntax();
		TCHAR	m_chValue;
		TCHAR	m_chDefaultValue;
		TCHAR	m_chMinValue;
		TCHAR	m_chMaxValue;
		BOOL	m_bIgnoreCase;
	};

}; //namespace QTUTILS

#endif //__QCMDOPTQCHAR_H__