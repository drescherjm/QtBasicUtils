#ifndef __QCMDOPTQSTRINGLIST_H__
#define __QCMDOPTQSTRINGLIST_H__

#include "QCmdOptBasicBase.h"
#include "QCmd.h"
#include <QStringList>

namespace QTUTILS {

	class QCmdOptQStringList : public QCmdOptBasicBase<QStringList>  
	{
	public:
		QCmdOptQStringList(QString strName, QString strDescription, QString strExplanation,  
			QStringList strDefaultValue, CMDSTRVERIFY pfnVerify);
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
		virtual QString GetShortSyntax( );
		virtual	void	Initialize();
	protected:
		void	Insert(QString str);
	protected:
		CMDSTRVERIFY	m_pFnVerify;
		bool			m_bWasDefault;
	};

}; //namespace QTUTILS

#endif //__QCMDOPTQSTRINGLIST_H__