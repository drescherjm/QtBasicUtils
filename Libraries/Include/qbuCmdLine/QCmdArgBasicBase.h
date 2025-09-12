#pragma once

#ifndef QCMDARGBASICBASE_H
#define QCMDARGBASICBASE_H

#include "qbuCmdLine/QCmdArg.h"

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE> class QCmdArgBasicBase : public QCmdArg  
{
public:
	QCmdArgBasicBase(QString strName, QString strDescription, QString strExplanation, 
		TYPE nDefaultValue);
	virtual QString GetSyntax()=0;
	virtual int		ImportData( QString strValue )=0;
	virtual void	Initialize();
	virtual bool	isDefaultValue();
	TYPE	GetValue();
	void	SetValue(TYPE nVal);
public:
	TYPE	m_nValue;
	TYPE	m_nDefaultValue;
};

/////////////////////////////////////////////////////////////////////////////////////////

#include "qbuCmdLine/QCmdArgBasicBase.txx"

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QCMDARGBASICBASE_H
