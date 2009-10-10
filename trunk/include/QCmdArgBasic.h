#ifndef __QCMDARGBASIC_H__
#define __QCMDARGBASIC_H__

#include "QCmdArgBasicBaseMM.h"
#include "QCmdExtra.h"

namespace QTUTILS {

template <class TYPE,char fmt[]> class QCmdArgBasic : public QCmdArgBasicBaseMM<TYPE>  
{
	typedef  QCmdArgBasicBaseMM<TYPE> SuperClass;
public:
	QCmdArgBasic(QString strName, QString strDescription, QString strExplanation, 
		TYPE nDefaultValue,TYPE nMinValue, TYPE nMaxValue);

	QCmdArgBasic(const QCmdArgBasic<TYPE, fmt> & other);
	QCmdArgBasic<TYPE, fmt>& operator=(const QCmdArgBasic<TYPE, fmt> & other);

	virtual QCmdArgBasic<TYPE, fmt>* Clone();
public:
	virtual QString GetSyntax();
	virtual QString exportCommandString();
	virtual int		ImportData( QString strValue );
private:
	void			copy( const QCmdArgBasic<TYPE, fmt> & other );
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmdArgBasic.txx"

/////////////////////////////////////////////////////////////////////////////////////////

typedef QCmdArgBasic<quint8,formatspec::BYTEFMT>	QCmdArg_quint8;
typedef QCmdArgBasic<quint16,formatspec::WORDFMT>	QCmdArg_quint16;
typedef QCmdArgBasic<quint32,formatspec::UINTFMT>	QCmdArg_quint32;
typedef QCmdArgBasic<int,formatspec::INTFMT>		QCmdArg_int;
typedef QCmdArgBasic<float,formatspec::FLTFMT>		QCmdArg_float;
typedef QCmdArgBasic<double,formatspec::DBLFMT>		QCmdArg_double;
typedef QCmdArgBasic<short,formatspec::SHORTFMT>	QCmdArg_short;

};//namespace QTUTILS

#endif //__QCMDARGBASIC_H__
