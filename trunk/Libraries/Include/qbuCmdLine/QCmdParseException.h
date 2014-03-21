//
// C++ Interface: QCmdParseException
//
// Description: 
//
//
// Author:  <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QString>
#include <QStringList>

#include "qbuCmdLine/QCmdParseError.h"



class QCmdParseException 
{
public:
	void Delete();
	static void Throw(quint32 nErrorCode, QString str0=(""), QString str1=(""));
	static void Throw(quint32 nErrorCode, QString str0, const QStringList & sl);
	static void Throw(quint32 nErrorCode, QString str0, const QStringList & sl,QString str2);
	quint32	GetErrorCode();
	QString	GetErrorString();
protected:
	quint32		m_nErrorCode;
	QString		m_strError;
private:
	QCmdParseException(quint32 nErrorCode, QString str0, QString str1,QString str2="");
};

inline QCmdParseException::QCmdParseException(quint32 nErrorCode, QString str0, QString str1,QString str2)
{
	m_nErrorCode = nErrorCode;
	m_strError = QCmdParseError::GetErrorString(nErrorCode,str0,str1,str2);
}

inline quint32 QCmdParseException::GetErrorCode()
{
	return m_nErrorCode;
}

inline QString QCmdParseException::GetErrorString()
{
	return m_strError;
}


