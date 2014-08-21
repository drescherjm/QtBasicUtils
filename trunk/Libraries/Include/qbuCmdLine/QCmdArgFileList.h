#pragma once

#ifndef __QCMDARGFILELIST_H__
#define __QCMDARGFILELIST_H__

#include "qbuCmdLine/QCmdArgBasicBase.h"
#include "qbuCmdLine/QCmdLineFileList.h"
#include "qbuCmdLine/QCmd.h"

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdArgFileList : public QCmdArgBasicBase<QCmdLineFileList>
{
	typedef QCmdArgBasicBase<QCmdLineFileList> SuperClass;
public:
	QCmdArgFileList(QString strName, QString strDescription, QString strExplanation, 
		QCmdLineFileList strDefaultValue, 
		CMDSTRVERIFY pfnVerify);
	QCmdArgFileList(const QCmdArgFileList & other);
	QCmdArgFileList& operator=(const QCmdArgFileList & other);
	virtual QCmdArgFileList* Clone();
public:
	virtual int			ImportData( QString strValue );
	virtual void		Initialize();
	virtual QString		GetSyntax();
	virtual QString		GetShortSyntax( );
	virtual QString		exportCommandString();
public:
	CMDSTRVERIFY		m_pFnVerify;
private:
	void			copy( const QCmdArgFileList & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __QCMDARGFILELIST_H__
