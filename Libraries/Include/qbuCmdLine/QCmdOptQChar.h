#pragma once

#ifndef QCMDOPTQCHAR_H
#define QCMDOPTQCHAR_H

#include "qbuCmdLine/QCmdOptBasicBaseMM.h"

/////////////////////////////////////////////////////////////////////////////////////////

class QCmdOptQChar : public QCmdOptBasicBaseMM<QChar>
{
	typedef QCmdOptBasicBaseMM<QChar> SuperClass;
public:
	QCmdOptQChar(QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase,
		QChar chDefaultValue, QChar chMinVal, QChar chMaxVal);
	QCmdOptQChar(const QCmdOptQChar & other);
	QCmdOptQChar& operator=(const QCmdOptQChar & other);
	virtual QCmdOptQChar* Clone();
public:
	virtual int		ImportData(QString strValue);
	virtual QString GetSyntax();
	virtual QString exportCommandString();
public:
	bool	m_bIgnoreCase;
private:
	void			copy(const QCmdOptQChar & other);
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QCMDOPTQCHAR_H
