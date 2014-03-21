#ifndef __QCMDARGQSTRINGLIST_H__
#define __QCMDARGQSTRINGLIST_H__

#include "qbuCmdLine/QCmdArgBasicBase.h"
#include "qbuCmdLine/QCmd.h"

#include <QStringList>

namespace QTUTILS {

	class QCmdArgQStringList : public QCmdArgBasicBase<QStringList>  
	{
		typedef QCmdArgBasicBase<QStringList> SuperClass;
	public:
		QCmdArgQStringList(QString str, QString strDescription, QString strExplanation,  
			QStringList strDefaultValue, CMDSTRVERIFY pfnVerify);
		QCmdArgQStringList(const QCmdArgQStringList & other);
		QCmdArgQStringList& operator=(const QCmdArgQStringList & other);
		virtual QCmdArgQStringList* Clone();
	public:
		virtual int		ImportData( QString strValue );
		virtual QString GetSyntax();
		virtual QString GetShortSyntax( );
		virtual	void	Initialize();
		virtual QString	exportCommandString();
	protected:
		void	Insert(QString strValue);
	protected:
		CMDSTRVERIFY	m_pFnVerify;
		bool			m_bWasDefault;
	private:
		void			copy( const QCmdArgQStringList & other );
		void			destroy();
	};

}; //namespace QTUTILS

#endif //__QCMDARGQSTRINGLIST_H__
