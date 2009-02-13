//
// C++ Interface: QCmdArg
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

class QCmdArg : public QCmdPart  
{
public:
	QCmdArg(QString strName,QString strDescription, QString strExplanation);
	virtual ~QCmdArg();
public:
	virtual bool GetOptional();
	virtual void SetOptional(bool bOptional);
	virtual QString GetSyntax( )=0;
	virtual QString GetShortSyntax( );
	bool m_bOptional;
	QString GetName();
protected:
	QString m_strName;
};

inline QString QCmdArg::GetName()
{
	return m_strName;
}

inline QString QCmdArg::GetShortSyntax()
{
	return GetName();
}

inline void QCmdArg::SetOptional(bool bOptional)
{
	m_bOptional = bOptional;
}

inline bool QCmdArg::GetOptional()
{
	return m_bOptional;
}

}; //namespace QTUTILS
