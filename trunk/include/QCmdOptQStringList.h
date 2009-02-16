#ifndef __QCMDOPTQSTRINGLIST_H__
#define __QCMDOPTQSTRINGLIST_H__

#include "QCmdOptBasicBase.h"

#include <QStringList>

namespace QTUTILS {

	class QCmdOptQStringList : public QCmdOptBasicBase<QStringList>  
	{
	public:
		QCmdOptQStringList(QString str, QString strDescription, QString strExplanation,  
			QStringList strDefaultValue, CMDSTRVERIFY pfnVerify);
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
		virtual QString GetShortSyntax( );
	protected:
		CMDSTRVERIFY	m_pFnVerify;
	};

}; //namespace QTUTILS

#endif //__QCMDOPTQSTRINGLIST_H__