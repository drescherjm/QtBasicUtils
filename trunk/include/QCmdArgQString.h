#ifndef __QCMDARGQSTRING_H__
#define __QCMDARGQSTRING_H__

#include "QCmdArgBasicBase.h"

namespace QTUTILS {

	class QCmdArgQString : public QCmdArgBasicBase<QString>  
	{
	public:
		QCmdArgQString(QString str, QString strDescription, QString strExplanation,  
			QString strDefaultValue, CMDSTRVERIFY pfnVerify);
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
	protected:
		CMDSTRVERIFY	m_pFnVerify;
	};

}; //namespace QTUTILS

#endif //__QCMDARGQSTRING_H__