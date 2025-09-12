#pragma once

#ifndef QCMDARGQSTRING_H
#define QCMDARGQSTRING_H

#include "qbuCmdLine/QCmdArgBasicBase.h"
#include "qbuCmdLine/QCmd.h"

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdArgQString : public QCmdArgBasicBase<QString>  
{
	typedef QCmdArgBasicBase<QString> SuperClass;
public:
	QCmdArgQString(QString str, QString strDescription, QString strExplanation,  
		QString strDefaultValue, CMDSTRVERIFY pfnVerify);
	QCmdArgQString(const QCmdArgQString & other);
	QCmdArgQString& operator=(const QCmdArgQString & other);
	virtual QCmdArgQString* Clone();
public:
	virtual int		ImportData( QString strValue );
	virtual QString GetSyntax();
	virtual QString exportCommandString();
protected:
	CMDSTRVERIFY	m_pFnVerify;
private:
	void			copy( const QCmdArgQString & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QCMDARGQSTRING_H
