#ifndef __QCMDOPTQSTRING_H__
#define __QCMDOPTQSTRING_H__

#include "QCmdOptBasicBase.h"
#include "QCmd.h"

namespace QTUTILS {

	class QCmdOptQString : public QCmdOptBasicBase<QString>  
	{
	public:
		QCmdOptQString(QString strName, QString strDescription, QString strExplanation,  
			QString strDefaultValue, CMDSTRVERIFY pfnVerify);
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
		virtual QString exportCommandString();
	protected:
		CMDSTRVERIFY	m_pFnVerify;
	};

}; //namespace QTUTILS

#endif //__QCMDOPTQSTRING_H__