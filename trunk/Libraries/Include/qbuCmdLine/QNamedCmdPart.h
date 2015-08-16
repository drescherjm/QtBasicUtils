#pragma once

#ifndef QNAMEDCMDPART_H
#define QNAMEDCMDPART_H

#include "qbuCmdLine/QCmdPart.h"

/////////////////////////////////////////////////////////////////////////////////////////

class QNamedCmdPart : public QCmdPart
{
public:
	QNamedCmdPart(QString strName,QString strDescription, QString strExplanation);
	QNamedCmdPart(const QNamedCmdPart & other);
	QNamedCmdPart& operator=(const QNamedCmdPart & other);
public:
	virtual QString GetSyntax( )=0;
	virtual QString GetShortSyntax( )=0;
	virtual bool	isDefaultValue()=0;
	virtual QString getValueDescription();
	virtual QString exportCommandString()=0;
	QString			GetName();
private:
	void			copy( const QNamedCmdPart & other );
	void			destroy();
protected:
	QString m_strName;
};

/////////////////////////////////////////////////////////////////////////////////////////

inline QString QNamedCmdPart::GetName()
{
	return m_strName;
}

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QNAMEDCMDPART_H
