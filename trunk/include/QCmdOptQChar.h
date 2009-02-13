#ifndef __QCMDOPTQCHAR_H__
#define __QCMDOPTQCHAR_H__

#include "QCmdOptBasicBase.h"

namespace QTUTILS {
	
	class QCmdOptQChar : public QCmdOptBasicBase<QChar>  
	{
	public:
		QCmdOptQChar(QChar ch, QString strDescription, QString strExplanation, bool bIgnoreCase, 
			QChar chDefaultValue, QChar chMinVal, QChar chMaxVal);
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
	public:
		bool	m_bIgnoreCase;
	};

}; //namespace QTUTILS

#endif //__QCMDOPTQCHAR_H__
