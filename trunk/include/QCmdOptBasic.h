#ifndef __QCMDOPTBASIC_H__
#define __QCMDOPTBASIC_H__

#include "QCmdOpt.h"

namespace QTUTILS {

template <class TYPE, QString fmt> class QCmdOptBasic : public QCmdOpt  
{
public:
	QCmdOptBasic(QChar ch, QString strDescription, QString strExplanation, TYPE nDefaultValue,
		TYPE nMinValue, TYPE nMaxValue);
	virtual QString GetSyntax();
	virtual int		ImportData( QString strValue );
	virtual void	Initialize();
	TYPE	GetValue();
public:
	TYPE	m_nValue;
	TYPE	m_nDefaultValue;
	TYPE	m_nMinValue;
	TYPE	m_nMaxValue;
};

/////////////////////////////////////////////////////////////////////////////////////////

#include "QCmdOptBasic.txx"

/////////////////////////////////////////////////////////////////////////////////////////

namespace formatspec 
{
	QString BYTEFMT = "%hu";
	QString WORDFMT = "%hu";
	QString UINTFMT = "%u";
	QString INTFMT = "%d";
	QString SHORTFMT = "%hd";
	QString FLTFMT = "%f";
	QString DBLFMT = "%lf";
}

typedef QCmdOptBasic<quint8,formatspec::BYTEFMT>	CCmdOpt_quint8;
typedef QCmdOptBasic<quint16,formatspec::WORDFMT>	CCmdOpt_quint16;
typedef QCmdOptBasic<quint32,formatspec::UINTFMT>	CCmdOpt_quint32;
typedef QCmdOptBasic<int,formatspec::INTFMT>		CCmdOpt_int;
typedef QCmdOptBasic<float,formatspec::FLTFMT>		CCmdOpt_float;
typedef QCmdOptBasic<double,formatspec::DBLFMT>		CCmdOpt_double;
typedef QCmdOptBasic<short,formatspec::SHORTFMT>	CCmdOpt_short;

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