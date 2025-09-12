#pragma once

#ifndef QCMDOPTBASICBASE_H
#define QCMDOPTBASICBASE_H

#include "qbuCmdLine/QCmdOpt.h"

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE> class QCmdOptBasicBase : public QCmdOpt  
{
public:
	QCmdOptBasicBase(QString strName, QString strDescription, QString strExplanation, 
		TYPE nDefaultValue);
	QCmdOptBasicBase(const QCmdOptBasicBase<TYPE> & other);
	QCmdOptBasicBase<TYPE>& operator=(const QCmdOptBasicBase<TYPE> & other);
public:
	virtual QString GetSyntax()=0;
	virtual int		ImportData( QString strValue )=0;
	virtual void	Initialize();
	virtual bool	isDefaultValue();
	TYPE			GetValue();
	void			SetValue(TYPE nVal);
public:
	TYPE	m_nValue;
	TYPE	m_nDefaultValue;
private:
	void			copy( const QCmdOptBasicBase & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#include "qbuCmdLine/QCmdOptBasicBase.txx"

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QCMDOPTBASICBASE_H
