//

#include <float.h>
#include <QString>
#include "QCmdLineFileList.h"
#include "QLimits.h"

namespace QTUTILS {

class QCmdArg;
class QCmdOpt;

typedef QList<QCmdArg*> QArgList;
typedef QList<QCmdOpt*> QOptList;

typedef QMap<QChar,QCmdOpt*> QOptMap;
typedef QMap<QString,QCmdArg*> QArgMap;

typedef int (*CMDSTRVERIFY)( QString str, qint32 nStr );
 
class QCmd
{
public:
	QCmd(QString strName,QString strDescription, QString strExplanation=QString(),bool bIgnoreCase = true);
	virtual ~QCmd();
public:
	virtual void Initialize();
public:
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, bool bDefaultValue = true);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, quint32 nDefaultValue = 0, quint32 nMinValue=0, 
		quint32 nMaxValue = quint32_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, int nDefaultValue = 0, int nMinValue=INT_MIN, 
		int nMaxValue = INT_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, quint8 nDefaultValue = 0, quint8 nMinValue=0, 
		quint8 nMaxValue = UCHAR_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, quint16 nDefaultValue = 0, quint16 nMinValue=0, 
		quint16 nMaxValue = USHRT_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, short nDefaultValue = 0, short nMinValue=SHRT_MIN, 
		short nMaxValue = SHRT_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, float nDefaultValue = 0, float nMinValue=FLT_MIN, 
		float nMaxValue = FLT_MAX);
	int	AddOpt( QChar ch, QString strDescription, QString strExplanation, double nDefaultValue = 0, double nMinValue=DBL_MIN, 
		double nMaxValue = DBL_MAX);
	int AddOpt( QChar ch, QString strDescription, QString strExplanation, bool bIgnoreCase=true, 
		QChar chDefaultValue=0x0, QChar chMinVal=SCHAR_MIN, QChar chMaxVal=SCHAR_MAX);

	int AddOpt( QChar ch, QString strDescription, QString strExplanation, QString strDefaultValue=(""), 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddOpt(QChar ch, QString strDescription, QString strExplanation, const  QStringList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);
	int	AddOpt(QChar ch, QString strDescription, QString strExplanation, const  QCmdLineFileList & strLstDefaultValue, 
		CMDSTRVERIFY pFnVerify=NULL);

	int AddArg( QString strName, QCmdArg* pArg=NULL);
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
	int	AddArg( QString strName, QString strDescription, QString strExplanation, float nDefaultValue = 0, float nMinValue=FLT_MIN, 
		float nMaxValue = FLT_MAX);
	int	AddArg( QString strName, QString strDescription, QString strExplanation, double nDefaultValue = 0, double nMinValue=DBL_MIN, 
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
	int GetOpt(QChar ch, bool & bValue);
	int GetOpt(QChar ch, quint32 & nValue);
	int GetOpt(QChar ch, int & nValue);
	int GetOpt(QChar ch, quint8 & nValue);
	int GetOpt(QChar ch, quint16 & nValue);
	int	GetOpt(QChar ch, short & nValue);
	int GetOpt(QChar ch, float & nValue);
	int GetOpt(QChar ch, double & nValue);
	int	GetOpt(QChar ch, char & chValue);
	int GetOpt(QChar ch, QString & nValue);
	int	GetOpt(QChar ch, QStringList & nValue);
	int	GetOpt(QChar ch, QCmdLineFileList & nValue);

	int GetArg(QString strName, bool & bValue);
	int GetArg(QString strName, quint32 & nValue);
	int GetArg(QString strName, int & nValue);
	int GetArg(QString strName, quint8 & nValue);
	int GetArg(QString strName, quint16 & nValue);
	int	GetArg(QString strName, short & nValue);
	int GetArg(QString strName, float & nValue);
	int GetArg(QString strName, double & nValue);
	int	GetArg(QString strName, char & chValue);
	int	GetArg(QString strName, QString & nValue);
	int	GetArg(QString strName, QStringList & nValue);
	int	GetArg(QString strName, QCmdLineFileList & nValue);
public:
	virtual int Parse();
	QStringList m_strLstCmd;
	virtual int Execute();
	void	EndRequiredArguments();
	int		IsOption( QString & str, QCmdOpt *& pOption );
	virtual QString GetSyntax();
	QString	GetName();
	QString GetDescription();
	QString GetLongDescription();
protected:
	int		Parse( QStringList & strLst );
	int		AddOpt( QChar ch, QCmdOpt* pOpt = NULL );
	QChar	GetOptChar( QChar ch );
	int		FindOpt( QChar ch, QCmdOpt *& option );
	int		FindArg(QString strName, QCmdArg *& ARGUMENT);
protected:
	QString		m_strName;
	bool		m_bOptional;
	bool		m_bIgnoreCase;
	QString		m_strDescription;
	QString		m_strExplanation;
	QOptList	m_listOptions;
	QArgList	m_listArguments;
	QOptMap		m_mapOpt;
	QArgMap		m_mapArg;
private:
	QString m_strStringListEnd;
	QChar m_chOption;
};

inline QString QCmd::GetName()
{
	return m_strName;
}

inline QString QCmd::GetDescription()
{
	return m_strDescription;
}

}; // namespace QTUTILS
