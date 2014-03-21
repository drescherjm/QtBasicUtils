#ifndef __QCMDLINE_H__
#define __QCMDLINE_H__

#include "qbuCmdLine/QCmd.h"

#include <QMap>
#include <QList>
#include <QTextStream>



/////////////////////////////////////////////////////////////////////////////////////////

	typedef QMap<QString,QCmd*> QCmdMap;
	typedef QList<QCmd*> QCmdList;
	typedef	QList<QStringList*> QStrLstList;

	class QCmdLine  
	{
	public:
		QCmdLine();
		virtual ~QCmdLine();
		QCmdLine(int argc, char* argv[]);
		QCmdLine( QString strProgName, QStringList & strLst );
		QCmdLine( QTextStream & args );
	public:
		int			Parse();
		QString		GetSyntax();
		int			AddCmd( QCmd* pCmd );
		QCmdList	getAvailableCommands();
		void		setAvailableCommands(QCmdList & lstCommands);

	public:
		typedef		QStrLstList::iterator iterator;
		iterator	begin();
		iterator	end();
		int			GetNextCommand(QCmdLine::iterator & it, QCmd *& pCmd);

	protected:
		int			ParseFile(QString strFileName,QStringList & strLstFile);
		int			ParseStream(QTextStream & args,QStringList & strLstFile);
		int			PreProcess(QStringList & strList);
		QCmd*		GetDefaultCmd();
		
		bool		IsCmdChar(QString str);
		QString		GetCommandString( QString strCmd);
		bool		IsHelpCmd(QString str);
		int			Parse( QStringList & strList);
	private:
		void		destroy();
	private:
		class		qtutilsPrivate;
		qtutilsPrivate* m_pPrivate;	
	};

/////////////////////////////////////////////////////////////////////////////////////////




#endif //__QCMDLINE_H__
