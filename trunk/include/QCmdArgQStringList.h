#ifndef __QCMDARGQSTRINGLIST_H__
#define __QCMDARGQSTRINGLIST_H__

#include "QCmdArgBasicBase.h"
#include "QCmd.h"

#include <QStringList>

namespace QTUTILS {

	class QCmdArgQStringList : public QCmdArgBasicBase<QStringList>  
	{
	public:
		QCmdArgQStringList(QString str, QString strDescription, QString strExplanation,  
			QStringList strDefaultValue, CMDSTRVERIFY pfnVerify);
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
		virtual QString GetShortSyntax( );
		virtual	void	Initialize();
	protected:
		CMDSTRVERIFY	m_pFnVerify;
	};

}; //namespace QTUTILS

#endif //__QCMDARGQSTRINGLIST_H__