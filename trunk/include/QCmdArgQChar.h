#ifndef __QCMDARGQCHAR_H__
#define __QCMDARGQCHAR_H__

#include "QCmdArgBasicBaseMM.h"

namespace QTUTILS {
	
	class QCmdArgQChar : public QCmdArgBasicBaseMM<QChar>  
	{
	public:
		QCmdArgQChar(QString strName, QString strDescription, QString strExplanation, 
			bool bIgnoreCase, 
			QChar chDefaultValue, QChar chMinVal, QChar chMaxVal);
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
	public:
		bool	m_bIgnoreCase;
	};

}; //namespace QTUTILS

#endif //__QCMDARGQCHAR_H__
