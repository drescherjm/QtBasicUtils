#ifndef __QCMDOPTBASIC_H__
#define __QCMDOPTBASIC_H__

#include "QCmdOptBasicBase.h"

namespace QTUTILS {

template <class TYPE,char fmt[]> class QCmdOptBasic : public QCmdOptBasicBase<TYPE>  
{
public:
	QCmdOptBasic(QChar ch, QString strDescription, QString strExplanation, 
		TYPE nDefaultValue,TYPE nMinValue, TYPE nMaxValue);
public:
	virtual QString GetSyntax();
	virtual int		ImportData( QString strValue );
};

/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmdOptBasic.txx"

/////////////////////////////////////////////////////////////////////////////////////////

namespace formatspec 
{
	char BYTEFMT[] = "%hu";
	char WORDFMT[] = "%hu";
	char UINTFMT[] = "%u";
	char INTFMT[] = "%d";
	char SHORTFMT[] = "%hd";
	char FLTFMT[] = "%f";
	char DBLFMT[] = "%lf";
}

typedef QCmdOptBasic<quint8,formatspec::BYTEFMT>	QCmdOpt_quint8;
typedef QCmdOptBasic<quint16,formatspec::WORDFMT>	QCmdOpt_quint16;
typedef QCmdOptBasic<quint32,formatspec::UINTFMT>	QCmdOpt_quint32;
typedef QCmdOptBasic<int,formatspec::INTFMT>		QCmdOpt_int;
typedef QCmdOptBasic<float,formatspec::FLTFMT>		QCmdOpt_float;
typedef QCmdOptBasic<double,formatspec::DBLFMT>		QCmdOpt_double;
typedef QCmdOptBasic<short,formatspec::SHORTFMT>	QCmdOpt_short;

/*
typedef CCmdArgNormal<BYTE,formatspec::BYTEFMT>		CCmdArgBYTE;
typedef CCmdArgNormal<WORD,formatspec::WORDFMT>		CCmdArgWORD;
typedef CCmdArgNormal<UINT,formatspec::UINTFMT>		CCmdArgUINT;
typedef CCmdArgNormal<int,formatspec::INTFMT>		CCmdArgint;
typedef CCmdArgNormal<float,formatspec::FLTFMT>		CCmdArgfloat;
typedef CCmdArgNormal<double,formatspec::DBLFMT>	CCmdArgdouble;
typedef CCmdArgNormal<short,formatspec::SHORTFMT>	CCmdArgshort;
*/

};//namespace QTUTILS

#endif //__QCMDOPTBASIC_H__