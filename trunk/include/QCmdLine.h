#ifndef __QCMDLINE_H__
#define __QCMDLINE_H__

#include "QCmd.h"

#include <QMap>
#include <QList>

namespace QTUTILS {

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
	public:
		int			Parse();
		QString		GetSyntax();
		int			AddCmd( QCmd* pCmd );

	public:
		typedef		QStrLstList::iterator iterator;
		iterator	begin();
		iterator	end();
		int			GetNextCommand(QCmdLine::iterator & it, QCmd *& pCmd);
	protected:
		int			ParseFile(QString strFileName,QStringList & strLstFile);
		int			PreProcess(QStringList & strList);
		QCmd*		GetDefaultCmd();
		void		destroy();
		bool		IsCmdChar(QString str);
		QString		GetCommandString( QString strCmd);
		bool		IsHelpCmd(QString str);
		void		Initialize();
		int			Parse( QStringList & strList);
	private:
		QStringList		m_strLstCmdLine;
		QStrLstList		m_strLstLstCmdLine;
		QCmdList		m_listCmds;
		QCmdMap			m_mapCmd;
		QString			m_strProgName;
		bool			m_bIgnoreCase;
		QChar			m_chCmdChar;
		QString			m_strCmdSep;
	};

/////////////////////////////////////////////////////////////////////////////////////////

}; //namespace QTUTILS


#endif //__QCMDLINE_H__