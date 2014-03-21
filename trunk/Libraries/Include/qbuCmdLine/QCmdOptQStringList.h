#ifndef __QCMDOPTQSTRINGLIST_H__
#define __QCMDOPTQSTRINGLIST_H__

#include "qbuCmdLine/QCmdOptBasicBase.h"
#include "qbuCmdLine/QCmd.h"
#include <QStringList>

namespace QTUTILS {

	class QCmdOptQStringList : public QCmdOptBasicBase<QStringList>  
	{
		typedef QCmdOptBasicBase<QStringList> SuperClass;
	public:
		QCmdOptQStringList(QString strName, QString strDescription, QString strExplanation,  
			QStringList strDefaultValue, CMDSTRVERIFY pfnVerify);
		QCmdOptQStringList(const QCmdOptQStringList & other);
		QCmdOptQStringList& operator=(const QCmdOptQStringList & other);
		virtual QCmdOptQStringList* Clone();
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
		virtual QString GetShortSyntax( );
		virtual	void	Initialize();
		virtual QString exportCommandString();
	protected:
		void	Insert(QString str);
	protected:
		CMDSTRVERIFY	m_pFnVerify;
		bool			m_bWasDefault;
	private:
		void			copy( const QCmdOptQStringList & other );
		void			destroy();
	};

}; //namespace QTUTILS

#endif //__QCMDOPTQSTRINGLIST_H__
