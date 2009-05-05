#ifndef __QCMDOPTBASIC_H__
#define __QCMDOPTBASIC_H__

#include "QCmdOptBasicBaseMM.h"

namespace QTUTILS {

template <class TYPE,char fmt[]> class QCmdOptBasic : public QCmdOptBasicBaseMM<TYPE>  
{
public:
	QCmdOptBasic(QString strName, QString strDescription, QString strExplanation, 
		TYPE nDefaultValue,TYPE nMinValue, TYPE nMaxValue);
public:
	virtual QString GetSyntax();
	virtual int		ImportData( QString strValue );
	virtual QString exportCommandString();
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

};//namespace QTUTILS

#endif //__QCMDOPTBASIC_H__