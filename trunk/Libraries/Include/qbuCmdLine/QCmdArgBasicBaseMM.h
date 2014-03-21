#pragma once

#ifndef __QCMDARGBASICBASEMM_H__
#define __QCMDARGBASICBASEMM_H__

#include "qbuCmdLine/QCmdArgBasicBase.h"

/////////////////////////////////////////////////////////////////////////////////////////

template <class TYPE> class QCmdArgBasicBaseMM : public QCmdArgBasicBase<TYPE>
{
	typedef  QCmdArgBasicBase<TYPE> SuperClass;
public:
	QCmdArgBasicBaseMM(QString strName, QString strDescription, QString strExplanation, 
		TYPE nDefaultValue,TYPE nMinValue, TYPE nMaxValue);
	virtual QString GetSyntax()=0;
	virtual int		ImportData( QString strValue )=0;

	QCmdArgBasicBaseMM(const QCmdArgBasicBaseMM<TYPE> & other);
	QCmdArgBasicBaseMM<TYPE>& operator=(const QCmdArgBasicBaseMM<TYPE> & other);
public:
	TYPE	m_nMinValue;
	TYPE	m_nMaxValue;
private:
	void			copy( const QCmdArgBasicBaseMM<TYPE> & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#include "qbuCmdLine/QCmdArgBasicBaseMM.txx"

/////////////////////////////////////////////////////////////////////////////////////////

#endif // __QCMDARGBASICBASEMM_H__
