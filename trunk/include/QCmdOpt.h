//
// C++ Interface: QCmdOpt
//
// Description: 
//
//
// Author:  <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

namespace QTUTILS {

class QCmdOpt : public QCmdPart  
{
public:
	QCmdOpt(QChar chLetter,QString strDescription, QString strExplanation);
	virtual ~QCmdOpt();
public:
	virtual int		ImportData( QString strValue )=0;
	virtual QString GetSyntax( )=0;
	virtual QString GetShortSyntax( );
	QChar	GetName();
protected:
	QChar m_chLetter;
};

inline QChar QCmdOpt::GetName()
{
	return m_chLetter;
}

inline QString QCmdOpt::GetShortSyntax()
{
	return GetName();
}


}; //namespace QTUTILS
