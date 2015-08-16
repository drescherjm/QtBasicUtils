#pragma once

#ifndef QCMDOPTBASICBASEMM_H
#define QCMDOPTBASICBASEMM_H

#include "qbuCmdLine/QCmdOptBasicBase.h"

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE> class QCmdOptBasicBaseMM : public QCmdOptBasicBase<TYPE>
{
public:
	QCmdOptBasicBaseMM(QString strName, QString strDescription, QString strExplanation, 
		TYPE nDefaultValue,TYPE nMinValue, TYPE nMaxValue);
	QCmdOptBasicBaseMM(const QCmdOptBasicBaseMM<TYPE> & other);
	QCmdOptBasicBaseMM<TYPE>& operator=(const QCmdOptBasicBaseMM<TYPE> & other);
	virtual QString GetSyntax()=0;
	virtual int		ImportData( QString strValue )=0;
public:
	TYPE			m_nMinValue;
	TYPE			m_nMaxValue;
private:
	void			copy( const QCmdOptBasicBaseMM & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#include "qbuCmdLine/QCmdOptBasicBaseMM.txx"

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QCMDOPTBASICBASEMM_H
