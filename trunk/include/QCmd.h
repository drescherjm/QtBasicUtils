#ifndef __QCMD_H__
#define __QCMD_H__
//

#include <float.h>
#include <QString>
#include <QMap>
#include "QCmdLineFileList.h"
#include "QLimits.h"
#include "QCmdArg.h"
#include "QCmdOpt.h"

namespace QTUTILS {

typedef QList<QCmdArg*> QArgList;
typedef QList<QCmdOpt*> QOptList;

typedef QMap< QString,QCmdOpt* > QOptMap;
typedef QMap< QString,QCmdArg* > QArgMap;

typedef int (*CMDSTRVERIFY)( QString str, qint32 nStr );

const float		NEG_FLOAT_MAX = -1.0f * FLT_MAX;
const double	NEG_DOUBLE_MAX = -1.0 * DBL_MAX;
 
class QCmd
{
public:
	QCmd(QString strName,QString strDescription, QString strExplanation=QString(),bool bIgnoreCase = true);
	QCmd(const QCmd & other);
	virtual ~QCmd();

	virtual QCmd* Clone();
	virtual QCmd* New();

public:
	virtual void Initialize();
public:
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, bool bDefaultValue = true);
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, quint32 nDefaultValue = 0, quint32 nMinValue=0, 
		quint32 nMaxValue = quint32_MAX);
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, int nDefaultValue = 0, int nMinValue=INT_MIN, 
		int nMaxValue = INT_MAX);
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, quint8 nDefaultValue = 0, quint8 nMinValue=0, 
		quint8 nMaxValue = UCHAR_MAX);
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, quint16 nDefaultValue = 0, quint16 nMinValue=0, 
		quint16 nMaxValue = USHRT_MAX);
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, short nDefaultValue = 0, short nMinValue=SHRT_MIN, 
		short nMaxValue = SHRT_MAX);
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, float nDefaultValue = 0, float nMinValue=NEG_FLOAT_MAX, 
		float nMaxValue = FLT_MAX);
	int	AddOpt( QString strName, QString strDescription, QString strExplanation, double nDefaultValue = 0, double nMinValue=NEG_DOUBLE_MAX, 
		double nMaxValue = DBL_MAX);
	int AddOpt( QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase, 
		QChar chDefaultValue, QChar chMinVal=SCHAR_MIN, QChar chMaxVal=SCHAR_MAX);

	int AddOpt( QString strName, QString strDescription, QString strExplanation, QString strDefaultValue=(""), 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddOpt(QString strName, QString strDescription, QString strExplanation, const  QStringList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddOpt(QString strName, QString strDescription, QString strExplanation, const  QCmdLineFileList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);

	//int AddArg( QString strName, QCmdArg* pArg=NULL);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, bool bDefaultValue = true);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, quint32 nDefaultValue = 0, quint32 nMinValue=0, 
		quint32 nMaxValue = quint32_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, int nDefaultValue = 0, int nMinValue=INT_MIN, 
		int nMaxValue = INT_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, quint8 nDefaultValue = 0, quint8 nMinValue=0, 
		quint8 nMaxValue = UCHAR_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, quint16 nDefaultValue = 0, quint16 nMinValue=0, 
		quint16 nMaxValue = USHRT_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, short nDefaultValue = 0, short nMinValue=SHRT_MIN, 
		short nMaxValue = SHRT_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, float nDefaultValue = 0, float nMinValue=NEG_FLOAT_MAX, 
		float nMaxValue = FLT_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, double nDefaultValue = 0, double nMinValue=NEG_DOUBLE_MAX, 
		double nMaxValue = DBL_MAX);
	int AddArg( QString strName, QString strDescription, QString strExplanation, bool bIgnoreCase=true, 
		QChar chNameDefaultValue=0x0, QChar chNameMinVal=SCHAR_MIN, QChar chNameMaxVal=SCHAR_MAX);
	int AddArg( QString strName, QString strDescription, QString strExplanation, QString strDefaultValue=(""), 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddArg(QString strName, QString strDescription, QString strExplanation,const  QStringList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddArg(QString strName, QString strDescription, QString strExplanation,const  QCmdLineFileList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);
public:
	int GetOpt(QString strName, bool & bValue);
	int GetOpt(QString strName, quint32 & nValue);
	int GetOpt(QString strName, int & nValue);
	int GetOpt(QString strName, quint8 & nValue);
	int GetOpt(QString strName, quint16 & nValue);
	int	GetOpt(QString strName, short & nValue);
	int GetOpt(QString strName, float & nValue);
	int GetOpt(QString strName, double & nValue);
	int	GetOpt(QString strName, QChar & chValue);
	int GetOpt(QString strName, QString & nValue);
	int	GetOpt(QString strName, QStringList & nValue);
	int	GetOpt(QString strName, QCmdLineFileList & nValue);

	int SetOpt(QString strName, bool bValue);
	int SetOpt(QString strName, quint32 nValue);
	int SetOpt(QString strName, int nValue);
	int SetOpt(QString strName, quint8 nValue);
	int SetOpt(QString strName, quint16 nValue);
	int	SetOpt(QString strName, short nValue);
	int SetOpt(QString strName, float nValue);
	int SetOpt(QString strName, double nValue);
	int	SetOpt(QString strName, QChar chValue);
	int SetOpt(QString strName, QString nValue);
	int	SetOpt(QString strName, QStringList nValue);
	int	SetOpt(QString strName, QCmdLineFileList nValue);

	int GetArg(QString strName, bool & bValue);
	int GetArg(QString strName, quint32 & nValue);
	int GetArg(QString strName, int & nValue);
	int GetArg(QString strName, quint8 & nValue);
	int GetArg(QString strName, quint16 & nValue);
	int	GetArg(QString strName, short & nValue);
	int GetArg(QString strName, float & nValue);
	int GetArg(QString strName, double & nValue);
	int	GetArg(QString strName, QChar & chValue);
	int	GetArg(QString strName, QString & nValue);
	int	GetArg(QString strName, QStringList & nValue);
	int	GetArg(QString strName, QCmdLineFileList & nValue);

	int SetArg(QString strName, bool bValue);
	int SetArg(QString strName, quint32 nValue);
	int SetArg(QString strName, int nValue);
	int SetArg(QString strName, quint8 nValue);
	int SetArg(QString strName, quint16 nValue);
	int	SetArg(QString strName, short nValue);
	int SetArg(QString strName, float nValue);
	int SetArg(QString strName, double nValue);
	int	SetArg(QString strName, QChar chValue);
	int SetArg(QString strName, QString nValue);
	int	SetArg(QString strName, QStringList nValue);
	int	SetArg(QString strName, QCmdLineFileList nValue);

public:
	virtual int Parse();
	virtual int Execute();
	void		EndRequiredArguments();
	//int			IsOption( QString & str, QCmdOpt *& pOption );
	virtual		QString GetSyntax();
	QString		GetName();
	QString		GetDescription();
	QString		GetLongDescription();
	bool		wasSuccessful(int nRetCode) const;
	
	// Basically the reverse of what parse does. This generates the string that can
	// be placed on the command line to initialize this command in the current state.
	QString		exportCommandString(QChar chCommand);
public:
	QStringList m_strLstCmd;
protected:
	int			Parse( QStringList & strLst );

	// When called with bDuplicate==true these clone the Options or Arguments instead of
	// using the same pointer. 
	QOptList	getOptions(bool bDuplicate=false) const;
	QArgList	getArguments(bool bDuplicate=false) const;

	int			FindOpt(QString strName, QCmdOpt *& option);
	int			FindArg(QString strName, QCmdArg *& pArg);
	
	void		setOptions(QOptList & lstOptions);
	void		setArguments(QArgList & lstArguments);
private:
	friend struct	qtutilsPrivate;
	struct			qtutilsPrivate;
	qtutilsPrivate* m_pPrivate;
private:
	void			copy(const QCmd & other);
	void			destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////

}; // namespace QTUTILS

#endif //__QCMD_H__